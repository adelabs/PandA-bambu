#this file is src/HLS/simulation/Makefile.am
noinst_LTLIBRARIES =  lib_simulation.la

lib_simulation_la_CPPFLAGS = \
   -I$(top_srcdir)/src \
   -I$(top_srcdir)/src/design_flows \
   -I$(top_srcdir)/src/design_flows/backend/ToC \
   -I$(top_srcdir)/src/design_flows/backend/ToC/progModels  \
   -I$(top_srcdir)/src/design_flows/backend/ToC/source_code_writers  \
   -I$(top_srcdir)/src/design_flows/backend/ToHDL  \
   -I$(top_srcdir)/src/behavior  \
   -I$(top_srcdir)/src/circuit  \
   -I$(top_srcdir)/src/constants  \
   -I$(top_srcdir)/src/frontend_analysis \
   -I$(top_srcdir)/src/frontend_analysis/IR_analysis \
   -I$(top_srcdir)/src/graph \
   -I$(top_srcdir)/src/HLS \
   -I$(top_srcdir)/src/HLS/binding \
   -I$(top_srcdir)/src/HLS/binding/interconnection \
   -I$(top_srcdir)/src/HLS/binding/module \
   -I$(top_srcdir)/src/HLS/binding/register \
   -I$(top_srcdir)/src/HLS/interface \
   -I$(top_srcdir)/src/HLS/memory \
   -I$(top_srcdir)/src/HLS/scheduling \
   -I$(top_srcdir)/src/HLS/vcd \
   -I$(top_srcdir)/src/HLS/virtual_components \
   -I$(top_srcdir)/src/parser/discrepancy \
   -I$(top_srcdir)/src/parser/polixml \
   -I$(top_srcdir)/src/polixml \
   -I$(top_srcdir)/src/technology \
   -I$(top_srcdir)/src/technology/physical_library \
   -I$(top_srcdir)/src/technology/target_device \
   -I$(top_srcdir)/src/tree  \
   -I$(top_srcdir)/src/utility \
   -I$(top_srcdir)/src/wrapper/flopoco \
   -I$(top_srcdir)/src/wrapper/treegcc \
   -I$(BOOST_DIR) $(all_includes)

METASOURCES = AUTO

noinst_HEADERS = \
   minimal_interface_testbench.hpp \
   testbench_generation.hpp \
   testbench_generation_base_step.hpp \
   wishbone_interface_testbench.hpp \
   test_vector_parser.hpp \
	testbench_memory_allocation.hpp \
	SimulationInformation.hpp

lib_simulation_la_SOURCES = \
   minimal_interface_testbench.cpp \
   testbench_generation.cpp \
   testbench_generation_base_step.cpp \
   wishbone_interface_testbench.cpp \
   test_vector_parser.cpp \
	testbench_memory_allocation.cpp

#DOCUMENTATION STUFF

#do not touch the following line

