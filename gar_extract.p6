# gar_extract.p6 --- simple gar file extractor

use v6;

# XXX MoveMethod enum NYI in rakudo
enum NYI_MoveMethod <FromStart FromCurrent FromEnd>;

sub MAIN(Str $filename, Str :o(:output($outdir)) = "./") {
    gar_extract($filename, $outdir);
    say "Done!";
}

sub gar_extract($filename, $outdir) {
    # the :nl part lets us read null-terminated strings easily, with .get .
    my $archive = open($filename, :bin, :nl("\0"));

    # check if it's a valid archive

    given $archive.read(4) -> $magic {
        if $magic.decode ne "GAR\x02" {
            $archive.close;
            die "Not a valid gaiden archive. Exiting.";
        }
    }

    # valid archive, let's get to extraction

    # info in the header
    my $arcsize     = bytes2num($archive.read(4));
    my $numtypes    = bytes2num($archive.read(2));
    my $numfiles    = bytes2num($archive.read(2));
    $archive.seek(0x10, FromStart);
    my $fnamepoint  = bytes2num($archive.read(4));
    my $filepoint   = bytes2num($archive.read(4));

    # get file type information
    my $entrybuf;
    my $nextentry;
    my $typename;
    my @typeindex;

    $archive.seek(0x20, FromStart);

    for ^$numtypes {
        $entrybuf = $archive.read(16);
        $nextentry = $archive.tell;

        # get filetype name
        $archive.seek(bytes2num($entrybuf[8..11]), FromStart);
        $typename = $archive.get.chop; # .chop removes the null character

        # get list of files of this type
        unless bytes2num($entrybuf[4..7]) == 0xFFFF_FFFF {
            $archive.seek(bytes2num($entrybuf[4..7]), FromStart);
            for ^bytes2num($entrybuf[0..3]) {
                @typeindex[bytes2num($archive.read(4))] = $typename;
            }
        }

        # get to next file type entry
        $archive.seek($nextentry, FromStart);
    }

    # get file names and size
    my @basenameindex;
    my @fsizeindex;
    my $bnpoint;

    $archive.seek($fnamepoint, FromStart);

    for ^$numfiles {
        # get file size
        @fsizeindex[$_] = bytes2num($archive.read(4));

        # get location of filename
        $bnpoint = bytes2num($archive.read(4));

        # store location of next entry
        $archive.seek(4, FromCurrent);
        $nextentry = $archive.tell;

        # get filename
        $archive.seek($bnpoint, FromStart);
        @basenameindex[$_] = $archive.get.chop;

        # go to next entry
        $archive.seek($nextentry, FromStart);
    }

    # get file pointers
    my @fpointindex;

    $archive.seek($filepoint, FromStart);

    @fpointindex[$_] = bytes2num($archive.read(4)) for ^$numfiles;

    # now to extract files
    my $curdata;
    my $curfile;
    my $curfname;
    my $byteswrote;

    for ^$numfiles {
        # find and read file
        $archive.seek(@fpointindex[$_], FromStart);
        $curdata = $archive.read(@fsizeindex[$_]);

        # write to file
        $curfname = $outdir;
        $curfname ~= "/" ~ @basenameindex[$_];
        $curfname ~= "." ~ @typeindex[$_];
        $curfile = open($curfname, :bin, :w);

        # XXX .write only returns True, should return bytes written
        #$byteswrote = $curfile.write($curdata);
        #$curfile.close;

        #if $byteswrote != $curdata.elems {
        #    note qq:to/EOT/;
        #    Warning for file \"$curfname\":
        #      Wrote    $byteswrote bytes,
        #      expected $curdata.elems() bytes.
        #    EOT
        #}

        $curfile.write($curdata);
        $curfile.close; 
    }
}

sub bytes2num($bytes) { :16($bytes.list».fmt("%02X").reverse.join) }