cflags=-std=c++11 -Wall -O2 -DLINUX

product=utillib.a

src= \
basenode.cpp \
field.cpp \
runtimeclass.cpp \
containers/array.cpp \
containers/intrusivelist.cpp \
containers/list.cpp \
containers/mfstring.cpp \
containers/ringlist.cpp \
containers/sfstring.cpp \
containers/stack.cpp \
geometry/boundingbox.cpp \
geometry/image.cpp \
geometry/matrix.cpp \
geometry/plane.cpp \
geometry/ray.cpp \
geometry/rect2d.cpp \
geometry/rotation.cpp \
geometry/sfcolor.cpp \
geometry/vec2f.cpp \
geometry/vec3f.cpp \
imglib/bitimage.cpp \
imglib/bmpdecod.cpp \
imglib/bmpencod.cpp \
imglib/imagetyp.cpp \
imglib/jfif.cpp \
imglib/jpdecomp.cpp \
imglib/jpdedu.cpp \
imglib/jpdehuff.cpp \
imglib/jpdequan.cpp \
imglib/jpeg.cpp \
imglib/jpegdeco.cpp \
imglib/jpegenco.cpp \
imglib/jpencomp.cpp \
imglib/jpendu.cpp \
imglib/jpenhuff.cpp \
imglib/jpenquan.cpp \
imglib/png.cpp \
imglib/pngchksm.cpp \
imglib/pngdecod.cpp \
imglib/pngencod.cpp \
imglib/pnghuffd.cpp \
imglib/pnghuffe.cpp

#-------------------------------------------------
# probably don't have to change below this line

objects = $(patsubst %.cpp,objs/%.o,$(src))

all:
	@echo "$(product) build started"
	@echo "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"
	@make $(product)
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

$(product): $(objects)
	-@$(RM) -f $*.a
	ar qc $*.a $(objects)
#	@chown jrush.jrush $(product)

$(objects): | objs

objs:
	@mkdir -p $@

objs/%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(cflags) -c $< -o $@

clean:
	-@$(RM) -f $(dest) $(product) objs/* 2> /dev/null
