if CREATEICONS
svgfile = $(srcdir)/../scalable/freenukum.svg
freenukum.png: $(svgfile)
	convert -scale 128x128 -background none $(svgfile) freenukum.png

icondir = $(datadir)/icons/hicolor/128x128/apps
icon_DATA = freenukum.png

clean:
	rm -f freenukum.png

EXTRA_DIST = $(icon_DATA)

endif # CREATEICONS
