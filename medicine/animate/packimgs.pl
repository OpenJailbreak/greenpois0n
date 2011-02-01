#!/usr/bin/perl
if (opendir(DIR, $ARGV[0])) {
	@IMGS = readdir(DIR);
	print "#ifndef _ANIMATE_FRAMES_BIN_H_\n#define _ANIMATE_FRAMES_BIN_H_\n\n";
	foreach (@IMGS) {
		if (/.*\.png$/i) {
			if (open(F, "<".$ARGV[0]."/".$_)) {
				binmode(F);
				$num = $_;
				$num =~ s/(.*)\.png$/$1/i;
				$out = 'const char VID_FRAME_' . $num . '[] = { ';
				$i = 0;
				$first = 1;
				$size = 0;
				
				while (!eof(F)) {
					if (!$first) {
						$out .= ", ";
					} else {
						$first = 0;
					}

					if ($i >= 15) {
						$out .= "\n\t\t";
						$i = 0;
					}

					$out .= sprintf("0x%02X", ord(getc(F)));
					$i++;
					$size++;
				}

				$out .= "};\n";
				$out .= 'int VID_FRAME_' . $num . '_SIZE = ' . $size . ";\n\n";
			}
			print $out;
		}
	}
	print "#endif\n";
}

