#===============================================================================
# Warlock Web (Emscripten) build
#
# This file was copied from Libraries/Warlock/Libraries/Framework/Web/Makefile
# into Platforms/Web/ and is yours to modify - 'rogo deps' will not overwrite it.
#
# Invoked by 'rogo web' as:  make -C Platforms/Web CONFIG=release|debug
# Output:                    Build/Web/App/index.{html,js,wasm,data}
#===============================================================================

APP_TITLE ?= Warlock App
CONFIG    ?= release

ROOT      := ../..
LIBS      := $(ROOT)/Libraries
BUILD     := $(ROOT)/Build/Web
OUT_DIR   := $(BUILD)/App
OBJ_DIR   := $(BUILD)/Obj/$(CONFIG)
SDL_BUILD := $(BUILD)/SDL

CC   := emcc
CXX  := em++

#-------------------------------------------------------------------------------
# Sources
#-------------------------------------------------------------------------------
APP_SOURCES  := Warlock.cpp $(BUILD)/Source/RogueProgram-Web.cpp
UTIL_SOURCES := $(LIBS)/Warlock/Libraries/Framework/C/Utilities.c
MA_SOURCES   := MiniAudio.cpp
SPINE_SOURCES := $(wildcard $(LIBS)/spine-runtimes/spine-cpp/src/spine/*.cpp)
TESS_SOURCES := $(addprefix $(LIBS)/libtess2/Source/, \
  bucketalloc.c dict.c geom.c mesh.c priorityq.c sweep.c tess.c)

SHELL_FILE := index.html
PRE_JS     := pre.js
ASSETS     := $(shell find $(BUILD)/Assets -type f 2>/dev/null)

#-------------------------------------------------------------------------------
# Prebuilt libraries
#-------------------------------------------------------------------------------
ifeq ($(CONFIG),debug)
  BGFX_SUFFIX := Debug
else
  BGFX_SUFFIX := Release
endif

BGFX_LIB_DIR := $(LIBS)/bgfx/.build/wasm/bin
# (genie's Emscripten naming omits the usual "lib" prefix.)
BGFX_LIBS    := $(addprefix $(BGFX_LIB_DIR)/, \
  bgfx$(BGFX_SUFFIX).a bimg_decode$(BGFX_SUFFIX).a \
  bimg$(BGFX_SUFFIX).a bx$(BGFX_SUFFIX).a)

SDL_LIB := $(SDL_BUILD)/libSDL3.a

#-------------------------------------------------------------------------------
# Flags
#-------------------------------------------------------------------------------
INCLUDES := \
  -I$(BUILD)/Source \
  -I$(LIBS)/Warlock/Libraries/Framework/C \
  -I$(LIBS)/SDL/include \
  -I$(LIBS)/bgfx/include \
  -I$(LIBS)/bx/include \
  -I$(LIBS)/bimg/include \
  -I$(LIBS)/miniaudio \
  -I$(LIBS)/spine-runtimes/spine-cpp/include \
  -I$(LIBS)/libtess2/Include

DEFINES := -Disnanf=isnan

ifeq ($(CONFIG),debug)
  OPT     := -O0 -g
  DEFINES += -DDEBUG=1 -DBX_CONFIG_DEBUG=1
  LINK_OPT := -O0 -g -sASSERTIONS=1
else
  OPT     := -O2
  DEFINES += -DNDEBUG -DBX_CONFIG_DEBUG=0
  LINK_OPT := -O2
endif

# Third-party code is always built optimized.
LIB_OPT := -O3 -DNDEBUG

WARNINGS := -Wno-nullability-completeness -Wno-unused-value

COMMON_FLAGS := $(DEFINES) $(INCLUDES) $(WARNINGS) -MMD -MP
CFLAGS       := $(COMMON_FLAGS)
# C++20 to match Xcode (gnu++20): generated Rogue code relies on parenthesized aggregate init.
CXXFLAGS     := $(COMMON_FLAGS) -std=c++20

LDFLAGS := \
  -sMIN_WEBGL_VERSION=2 \
  -sMAX_WEBGL_VERSION=2 \
  -sALLOW_MEMORY_GROWTH=1 \
  -sSTACK_SIZE=4MB \
  -sEXIT_RUNTIME=0 \
  -sEXPORTED_RUNTIME_METHODS=FS,callMain \
  -lidbfs.js \
  --pre-js $(PRE_JS) \
  --shell-file $(SHELL_FILE) \
  --preload-file $(BUILD)/Assets@/Assets

#-------------------------------------------------------------------------------
# Object lists
#-------------------------------------------------------------------------------
# obj_name(source) -> unique object path under OBJ_DIR (by basename)
obj_name = $(OBJ_DIR)/$(1)/$(notdir $(basename $(2))).o

APP_OBJS   := $(foreach s,$(APP_SOURCES),  $(call obj_name,app,$(s)))
UTIL_OBJS  := $(foreach s,$(UTIL_SOURCES), $(call obj_name,utilities,$(s)))
MA_OBJS    := $(foreach s,$(MA_SOURCES),   $(call obj_name,miniaudio,$(s)))
SPINE_OBJS := $(foreach s,$(SPINE_SOURCES),$(call obj_name,spine,$(s)))
TESS_OBJS  := $(foreach s,$(TESS_SOURCES), $(call obj_name,tess2,$(s)))

OBJS := $(APP_OBJS) $(UTIL_OBJS) $(MA_OBJS) $(SPINE_OBJS) $(TESS_OBJS)

#-------------------------------------------------------------------------------
# Targets
#-------------------------------------------------------------------------------
.PHONY: all sdl clean clean-all

all: $(OUT_DIR)/index.html

$(OUT_DIR)/index.html: $(OBJS) $(SDL_LIB) $(BGFX_LIBS) $(SHELL_FILE) $(PRE_JS) $(ASSETS)
	@mkdir -p $(OUT_DIR)
	$(CXX) $(LINK_OPT) $(OBJS) $(SDL_LIB) $(BGFX_LIBS) $(LDFLAGS) -o $@
	@# Tell the shell page's progress bar how many bytes it is waiting for.
	@total=$$(( $$(wc -c < $(OUT_DIR)/index.wasm) + $$(wc -c < $(OUT_DIR)/index.data) )); \
	 sed -e "s/__WARLOCK_TOTAL_BYTES__/$$total/g" $@ > $@.tmp && mv $@.tmp $@; \
	 echo "Total download: $$total bytes"

# SDL3 static library, built with emscripten's CMake wrapper.
sdl: $(SDL_LIB)

$(SDL_LIB):
	emcmake cmake -S $(LIBS)/SDL -B $(SDL_BUILD) \
	  -DCMAKE_BUILD_TYPE=Release \
	  -DSDL_SHARED=OFF -DSDL_STATIC=ON \
	  -DSDL_TESTS=OFF -DSDL_EXAMPLES=OFF -DSDL_INSTALL=OFF
	cmake --build $(SDL_BUILD) --parallel

$(BGFX_LIBS):
	@echo "Missing $@ - run 'rogo deps web' to build bgfx for Web." && exit 1

clean:
	rm -rf $(BUILD)/Obj $(OUT_DIR)

clean-all: clean
	rm -rf $(SDL_BUILD)

#-------------------------------------------------------------------------------
# Compile rules
#   $(1) = source file  $(2) = group  $(3) = extra flags
#-------------------------------------------------------------------------------
define cxx_rule
$(call obj_name,$(2),$(1)): $(1)
	@mkdir -p $$(dir $$@)
	$(CXX) $(CXXFLAGS) $(3) -c $$< -o $$@
endef

define c_rule
$(call obj_name,$(2),$(1)): $(1)
	@mkdir -p $$(dir $$@)
	$(CC) $(CFLAGS) $(3) -c $$< -o $$@
endef

$(foreach s,$(APP_SOURCES),  $(eval $(call cxx_rule,$(s),app,$(OPT))))
$(foreach s,$(MA_SOURCES),   $(eval $(call cxx_rule,$(s),miniaudio,$(LIB_OPT))))
$(foreach s,$(SPINE_SOURCES),$(eval $(call cxx_rule,$(s),spine,$(LIB_OPT))))
$(foreach s,$(UTIL_SOURCES), $(eval $(call c_rule,$(s),utilities,$(LIB_OPT))))
$(foreach s,$(TESS_SOURCES), $(eval $(call c_rule,$(s),tess2,$(LIB_OPT))))

-include $(OBJS:.o=.d)
