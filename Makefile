###############################################################################
###################### <github.com/aszdrick/magefile/> ########################
############################ <aszdrick@gmail.com> #############################
###############################################################################
# Copyright (c) 2017 Marleson Graf

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in 
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

################################# DEFINITIONS #################################
# Directories
SRCDIR   :=src
HDRDIR   :=include
OBJDIR   :=build
BINDIR   :=bin
TESTDIR  :=tests
DEPDIR   :=.deps
# Compiler & linker flags
CXXFLAGS :=-Wall -std=c++11
LDFLAGS  :=
LDLIBS   :=
INCLUDE  :=-I$(HDRDIR)
# Files
MAIN     :=main
EXEC     :=$(BINDIR)/lb-framework
# Project files
SRC      :=$(shell find $(SRCDIR) -name '*.cpp' 2> /dev/null)
DEP      :=$(patsubst %.cpp,$(DEPDIR)/%.d,$(SRC))
OBJ      :=$(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))
# Test files
PUREOBJ  :=$(filter-out $(OBJDIR)/$(SRCDIR)/$(MAIN).o,$(OBJ))
TSRC     :=$(shell find $(TESTDIR) -name '*.cpp' 2> /dev/null)
TMAIN    :=$(wildcard $(TESTDIR)/*.cpp)
TDEP     :=$(patsubst %.cpp,$(DEPDIR)/%.d,$(TSRC))
TOBJ     :=$(patsubst %.cpp,$(OBJDIR)/%.o,$(TSRC))
TPUREOBJ :=$(filter-out $(patsubst %.cpp,$(OBJDIR)/%.o,$(TMAIN)),$(TOBJ))
TEXEC    :=$(patsubst $(TESTDIR)/%.cpp,$(BINDIR)/%,$(TMAIN))
TCALL    :=$(patsubst %.cpp,%,$(notdir $(TMAIN)))
# Autogenerated directories, usefull to quickly create directories structure
MAKEDIR  :=$(BINDIR) $(SRCDIR) $(HDRDIR)

.PHONY: all makedir clean clean-all tests

################################# MAIN RULES ##################################
all: makedir $(EXEC)

$(EXEC): $(OBJ)
	@echo "[linking] $@"
	@$(CXX) $(OBJ) -o $@ $(LDLIBS) $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	@echo "[  $(CXX)  ] $< -> .o"
	@mkdir -p $(OBJDIR)/$(*D)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# For each .cpp file, creates a .d file with all dependencies of .cpp,
# including .d as target (to ensure up-to-date dependencies, in case of
# new includes being added)
$(DEPDIR)/%.d: %.cpp
	@echo "[makedep] $< -> .d"
	@mkdir -p $(DEPDIR)/$(*D)
	@$(CXX) -MM -MP -MG -MT "$(OBJDIR)/$*.o $@" -MF "$@" $< $(INCLUDE) $(CXXFLAGS)

makedir: | $(MAKEDIR)

$(MAKEDIR):
	@echo "[ mkdir ] Creating directory '$@'"
	@mkdir -p $@

################################ TESTS RULES ##################################
tests: makedir $(TCALL) $(TEXEC)

$(foreach t,$(TCALL),$(t): $(PUREOBJ) $(TPUREOBJ) $(OBJDIR)/$(TESTDIR)/$(t).o)

$(TEXEC): LDFLAGS+=-lgtest 

$(TEXEC): $(PUREOBJ) $(TPUREOBJ) $(TMAIN)
	@echo "[linking] $@"
	@$(CXX) $(PUREOBJ) $(TOBJ) -o $@ $(LDLIBS) $(LDFLAGS)

################################ CLEAN RULES ##################################
# Only remove object files
clean: $(MCLEAN)
	@$(RM) -r $(OBJDIR)

# Remove object, binary and dependency files
clean-all: clean $(MCLNALL)
	@$(RM) -r $(BINDIR)
	@$(RM) -r $(DEPDIR)

################################ PREREQUISITES ################################
# Do not include list of dependencies with clean rules
ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), clean-all)
ifneq ($(MAKECMDGOALS), cleanest)
  -include $(DEP)
  ifeq ($(MAKECMDGOALS), tests)
	-include $(TDEP)
  endif
endif
endif
endif