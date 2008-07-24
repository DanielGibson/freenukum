if CREATEICONS
svgfile = $(srcdir)/../scalable/freenukum.svg
freenukum.png: $(svgfile)
	convert -scale 24x24 -background none $(svgfile) freenukum.png

icondir = $(datadir)/icons/hicolor/24x24/apps
icon_DATA = freenukum.png

clean:
	rm -f freenukum.png

EXTRA_DIST = $(icon_DATA)

endif # CREATEICONS
