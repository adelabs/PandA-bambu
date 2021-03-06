/*
 *
 *                   _/_/_/    _/_/   _/    _/ _/_/_/    _/_/
 *                  _/   _/ _/    _/ _/_/  _/ _/   _/ _/    _/
 *                 _/_/_/  _/_/_/_/ _/  _/_/ _/   _/ _/_/_/_/
 *                _/      _/    _/ _/    _/ _/   _/ _/    _/
 *               _/      _/    _/ _/    _/ _/_/_/  _/    _/
 *
 *             ***********************************************
 *                              PandA Project 
 *                     URL: http://panda.dei.polimi.it
 *                       Politecnico di Milano - DEIB
 *                        System Architectures Group
 *             ***********************************************
 *              Copyright (c) 2004-2018 Politecnico di Milano
 *
 *   This file is part of the PandA framework.
 *
 *   The PandA framework is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
*/
/**
 * @file translator.hpp
 * @brief Dump information read already read from profiling file to other files
 *
 * @author Marco Lattuada <lattuada@elet.polimi.it>
 * $Revision$
 * $Date$
 * Last modified by $Author$
 *
*/
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

///Autoheader include
#include "config_HAVE_RTL_BUILT.hpp"

#if HAVE_RTL_BUILT
///RTL include
#include "rtl_common.hpp"
#endif

///STD include
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

///STL include
#include <map>
#include <unordered_map>
#include <unordered_set>

///Utility include
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include "custom_map.hpp"
#include "refcount.hpp"

/**
 * @name forward declarations
 */
//@{
CONSTREF_FORWARD_DECL(Parameter);
enum class Parameters_FileFormat;
REF_FORWARD_DECL(XMLDomParser);
//@}

#define TEXT_FORMAT (text) (number) (exponential)

#define TF_ENUM(r, data, elem) BOOST_PP_CAT(TF_, elem),

#define COMPARISON_OPERATOR (abs_le)

#define CO_ENUM(r, data, elem) BOOST_PP_CAT(CO_, elem),

#define TOTAL_FORMAT (average) (overall) (none)

#define TOF_ENUM(r, data, elem) BOOST_PP_CAT(TOF_, elem),

/**
 * Class to translate data from a format to another one
*/
class Translator
{
   private:
      ///the set of parameters
      const ParameterConstRef Param;

      ///the debug level
      int debug_level;

      ///Class describing the characteristic of a column of latex table
      class LatexColumnFormat
      {
         public:
            ///Text format
            typedef enum
            {
               BOOST_PP_SEQ_FOR_EACH(TF_ENUM, BOOST_PP_EMPTY, TEXT_FORMAT)
            } TextFormat;

            ///Comparison operator
            typedef enum
            {
               BOOST_PP_SEQ_FOR_EACH(CO_ENUM, BOOST_PP_EMPTY, COMPARISON_OPERATOR)
            } ComparisonOperator;

            ///Total format
            typedef enum
            {
               BOOST_PP_SEQ_FOR_EACH(TOF_ENUM, BOOST_PP_EMPTY, TOTAL_FORMAT)
            } TotalFormat;

         private:
            ///Map string->enum for text format
            static
            std::unordered_map<std::string, TextFormat> string_to_TF;

            ///Map string->enum for comparison operator
            static
            std::unordered_map<std::string, ComparisonOperator> string_to_CO;

            ///Map string->enum for total format
            static
            std::unordered_map<std::string, TotalFormat> string_to_TOF;

         public:
            ///The name of the column
            std::string column_name;

            ///The prefix of the columns
            std::vector<std::string> columns_prefix;

            ///The xml name of this column
            std::string source_name;

            ///The alignment of the column
            std::string column_alignment;

            ///The text format of the column
            TextFormat text_format;

            ///The precision of the number
            std::streamsize precision;

            ///The columns with which this has to be compared
            std::unordered_set<std::string> compared_columns;

            ///The operator of the comparison
            ComparisonOperator comparison_operator;

            ///The format of the total of this column
            TotalFormat total_format;

            /**
             * Constructor
             */
            LatexColumnFormat();

            /**
             * Given a string return the corresponding enum
             * @param string is the string to be analyzed
             */
            static
            TextFormat get_TF(const std::string&string);

            /**
             * Given a string return the corresponding enum
             * @param string is the string to be analyzed
             */
            static
            ComparisonOperator get_CO(const std::string&string);

            /**
             * Given a string return the corresponding enum
             * @param string is the string to be analyzed
             */
            static
            TotalFormat GetTotalFormat(const std::string&string);

            /**
             * Return A operator B
             * @param A is the first operand
             * @param comparator is the operator to be applied
             * @param B is the second operand
             * @return true if A operator B
             */
            static
            bool Compare(const long double A, const ComparisonOperator comparator, const long double B);
      };

      /**
       * Read normalization file
       * @param normalization is where normalize data will be stored
       */
      void get_normalization(std::unordered_map<std::string, long double> & normalization) const;

      /**
       * Return a number in latex exponential notation
       * @param input is the number to be translated
       * @return the string in exponential notation
       */
      std::string get_exponential_notation(const std::string& input)const ;

      /**
       * Replace '_' with ' '
       * @param ioString is the string to be converted
       */
      static
      void replace_underscore(std::string& ioString);

      /**
       * Read latex column format from xml
       * @param parser is the parser used to parse the stream
       * @param latex_column_formats is where read data will be put
       * @param max_column_width is where maximum column width will be stored
       */
      void read_column_formats(const XMLDomParserRef parser, std::list<LatexColumnFormat> & latex_column_formats, size_t & max_column_width) const;

   public:
     /**
       * Constructor
       * @param Param is the set of the parameters
       */
      explicit Translator(const ParameterConstRef Param);

#if HAVE_RTL_BUILT
      /**
       * Translate data from rapid_miner to rtl format
       * @param input is the data
       * @param output is where the data will be stored
       */
      void Translate(std::unordered_map<std::string, long double> input, std::map<enum rtl_kind, std::map<enum mode_kind, long double> > & output) const;

      /**
       * Write rtl data to xml
       * @param data is the data to be written
       * @param file_name is the name of the file where data will be written
       */
      void write_to_xml(const std::map<enum rtl_kind, std::map<enum mode_kind, long double> > & data, std::string file_name) const;
#endif

      /**
       * Write rtl data in csv format
       * @param tags is the column to be written
       * @param data is the data to be written
       * @param file_name is the name of the file where data will be written
       */
      void write_to_csv(const std::map<std::string, std::set<std::string> > & tags, const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, long double> > > & results, const std::string&file_name) const;

      /**
       * Write text data in csv format
       * @param results is the data to be written
       * @param file_name is the name of the file
       */
      void write_to_csv(const std::unordered_map<std::string, std::list<std::pair<std::string, std::string> > > & results, const std::string& file_name) const;

      /**
       * Write profiling analysis to pa
       * @param tags is the column to be written
       * @param data is the data to be written
       * @param file_name is the name of the file where data will be written
       */
      void write_to_pa(const std::map<std::string, std::set<std::string> > & tags, const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, long double> > > & results, const std::string&file_name) const;

      /**
       * Write data in latex table format
       * @param results is the data to be written
       * @param file_name is the name of the files
       */
      void write_to_latex(std::map<std::string, CustomMap<std::string, std::string> > & results, const Parameters_FileFormat input_format, const std::string& file_name) const;

      /**
       * Merget profiling analysis
       * @param tags is the column to be written
       * @param keys is the column to be written
       * @param input_data are the data of the first profiling analysis
       * @param merge_data are the data to be merged with the first profiling analysis
       * @param output_data is where data will be stored
       */
      void merge_pa
      (
         const std::map<std::string, std::set<std::string> > & tags,
         const std::unordered_map<std::string, std::set<std::string> > & keys,
         const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, long double> > > & input_data,
         const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, long double> > > & merge_data,
         std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, long double> > > & output_data
      ) const;

      /**
       * Collapse columns of data considering super classes and remove selected rows
       * @param data are the data to be collapsed
       * @param column_names are the names of the column
       * @param Param is the set of input parameters
       */
      static
      void AggregateAndClean(std::map<std::string, std::map<std::string, long double> > & data, std::set<std::string> & column_names, const ParameterConstRef param);
};

typedef refcount<const Translator> TranslatorConstRef;
#endif
