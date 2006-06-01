// vim:tabstop=4:shiftwidth=4:noexpandtab:textwidth=80
/*
 * $RCSfile$
 *
 * $Log$
 * Revision 1.6  2006/06/01 14:46:24  hockm0bm
 * doc update - doxygen warnings removed (if possible)
 *
 * Revision 1.5  2006/06/01 14:05:05  hockm0bm
 * * trim method added
 * * tokenizer method signature changed
 *         - text and deliminers parameters are const & now
 *
 * Revision 1.4  2006/06/01 09:12:30  hockm0bm
 * tokenizer function
 *         - moved to configuration::utils namespace
 *         - empty strings are not parsed
 *         - bug fix last token is also considered (when text is not
 *           finished by deliminer)
 *
 * Revision 1.3  2006/06/01 08:49:12  hockm0bm
 * * confparser.cc module added
 * * tokenizer function added
 *
 * Revision 1.2  2006/05/31 22:35:03  hockm0bm
 * * IConfigurationParser
 *         - stream is stored in the the class
 *         - it can be changed in runtime by setStream method
 * * StringConfigurationParser
 *         - stream removed from class (it is in super class)
 *         - handles no stream present
 *
 * Revision 1.1  2006/05/31 20:44:10  hockm0bm
 * * IConfigurationParser interface added
 * * StringConfigurationParser basic implemetation
 *
 *
 */
#ifndef _CONFPARSER_H_
#define _CONFPARSER_H_

#include<iostream>
#include<string>
#include<vector>

namespace configuration
{

// defines helper functions for parsing
namespace utils
{
	
/** Parses given text to tokens.
 * @param text String to parse.
 * @param deliminers Set of deliminers.
 * @param tokens Output array of tokens.
 *
 * One token is considered to be everything between two deliminers (or text
 * start, end respectively). Deliminers are not included. Note that empty string
 * is ignored and not parsed.
 *
 * @return number of output tokens.
 */
size_t tokenizer(const std::string & text, const std::string & deliminers, std::vector<std::string> & tokens);

/** Trims given string.
 * @param str String to trim.
 * @param blankSet Set of blank characters (default value " \t\n").
 *
 * Removes leading and trailing characters which are in blankSet.
 *
 * @return reference to trimed str.
 */
std::string & trim(std::string & str, const std::string & blankSet=" \t\n");

} // namespace configuration::utils

/** Interface for configuration parsers.
 * Defines methods needed for parsing configuration file. Template paramters
 * specifies concrete types for configuration entities which allways consist of
 * two parts key and value, where key determines meaning of value. Implementator
 * gives meaning to both of them.
 * <br>
 * Current unparsed key, value pair may be skipped by skip method.
 * <br>
 * Note that this interface doesn't say how format looks like or whether data
 * are read by lines or what so ever. One parse method call fills key and value
 * and moves to following one or returns with false if no more data are
 * available.
 * <br>
 * Data are read from input stream which is set in constructor and stored in 
 * this class as protected field. Stream may be changed by setStream method.
 */
template<typename KeyType=std::string, typename ValueType=std::string>
class IConfigurationParser
{
protected:
	/** Stream with data.
	 */
	std::istream * stream;
public:
	/** Empty constructor.
	 * Initializes stream to NULL.
	 */
	IConfigurationParser():stream(NULL){}
	
	/** Initialization constructor.
	 * @param str Stream with data.
	 *
	 * Sets stream field.
	 */
	IConfigurationParser(std::istream * str):stream(str){}
	
	/** Empty virtual destructor.
	 */
	virtual ~IConfigurationParser(){}

	/** Skipps current key, value pair.
	 */
	virtual void skip()=0;

	/** Sets new data stream.
	 * @param str Stream to set.
	 *
	 * Sets new value of stream.
	 *
	 * @return Current stream.
	 */
	virtual std::istream * setStream(std::istream * str)
	{
		std::istream * old=stream;

		stream=str;

		return old;
	}
	
	/** Parse current key, value pair.
	 * @param key Reference where to put parsed key.
	 * @param value Reference where to put parsed value.
	 *
	 * Moves current parsing position after parsed data.
	 *
	 * @return true if parsing was successfull or false otherwise.
	 */
	virtual bool parse(KeyType & key, ValueType & value)=0;

	/** Checks whether we are on end of data.
	 *
	 * Allways returns true if no stream is specified (it is NULL).
	 * @return true if there is nothing more to read, false otherwise.
	 */
	virtual bool eod()=0;
};

/** Simple string parser.
 * Reads input stream by lines and split line according deliminer. Everything
 * before deliminers member is marked as key and everything after as value. 
 * <br>
 * Deliminers are specified as set of characters where each stands for
 * separator. 
 */
class StringConfigurationParser: public IConfigurationParser<std::string, std::string>
{
	/** Set of deliminers.
	 * Each character is one deliminer.
	 * Default value contains `:' character.
	 */
	std::string deliminerSet;

	/** Set of characters for comments.
	 * Default value contains `%', `#' characters.
	 */
	std::string commentsSet;

	/** Set of characters for blanks.
	 * Default value contains ` ', `\t' characters.
	 */
	std::string blankSet;

	/** Maximum line length constant.
	 */
	static const size_t LINELENGTH=1024;
public:
	/** Initialization constructor.
	 * @param str Input stream with data.
	 *
	 * Initializes stream field with str and initializes *Set fields with
	 * default values.
	 */
	StringConfigurationParser(std::istream * str):IConfigurationParser<std::string, std::string>(str)
	{
		deliminerSet=":";
		commentsSet="%#";
		blankSet=" \t";
	};

	/** Sets new commentsSet.
	 * @param set Set of characters.
	 *
	 * @return Current set value.
	 */
	std::string setCommentsSet(std::string set)
	{
		std::string old=commentsSet;

		commentsSet=set;

		return old;
	}

	/** Sets new blankSet.
	 * @param set Set of characters.
	 *
	 * @return Current set value.
	 */
	std::string setBlankSet(std::string set)
	{
		std::string old=blankSet;

		blankSet=set;

		return old;
	}

	/** Sets new deliminerSet.
	 * @param set Set of characters.
	 *
	 * @return Current set value.
	 */
	std::string setDeliminersSet(std::string set)
	{
		std::string old=deliminerSet;

		deliminerSet=set;

		return old;
	}

	/** Reads one line and throw it away.
	 *
	 * If no stream is specified, immediately returns.
	 */
	void skip()
	{
		if(!stream)
			return;

		// reads one line and forget it
		char buffer[LINELENGTH];
		stream->getline(buffer, LINELENGTH);
	}

	/** Parses valid line.
	 * Reads line from current stream position. Removes comments (everything
	 * behind membet of commentsSet character). Removes intials and trailing
	 * blanks (all characters from blankSet). If result data are empty, parses
	 * following line. Otherwise starts parsing.
	 * <br>
	 * Parsing process is very simple and just searches first occurence of
	 * character from deliminerSet. Everything before separator is used to
	 * initialize key parameter and everything behind to value parameter. If
	 * none from deliminerSet is found assumes that value is empty and key is
	 * whole parsed string.
	 * <br>
	 * If any error occures while reading or end of file occured, returns with
	 * false and key, value parameters are not filled.
	 * <br>
	 * If no stream is set, immediately returns with false.
	 * <br>
	 * Note that input stream can't contain 0 characters.
	 *
	 * @return true if line was parsed or false otherwise.
	 */
	bool parse(std::string & key, std::string & value)
	{
	using namespace std;

		if(!stream)
			return false;

		char buffer[LINELENGTH];
		char *bufferStart;
		memset(buffer, '\0', sizeof(buffer));

		// proccess one line until it is non empty
		do
		{
			if(stream->eof())
				return false;
			
			stream->getline(buffer, LINELENGTH);
			bufferStart=buffer;
			if(stream->bad())
				// error during reading occured
				return false;

			// removes leading blanks
			for(size_t pos=0; pos<LINELENGTH; pos++)
			{
				if(blankSet.find(*bufferStart)!=string::npos)
					bufferStart++;
				else
					break;
			}
			
			// skips comments
			if(char * commentStart=strpbrk(bufferStart, commentsSet.c_str()))
				*commentStart='\0';

			// skips trailing blanks (no leading are present)
			for(char * end=bufferStart+strlen(bufferStart)-1; end>bufferStart; end--)
			{
				if(blankSet.find(*end)!=string::npos)
					*end='\0';
				else
					break;
			}
		}while(!(*bufferStart));

		// we have read one non empty line we can parse it to get key and value
		if(char * delim=strpbrk(bufferStart, deliminerSet.c_str()))
		{
			*delim='\0';
			key=bufferStart;
			value=delim+1;
		}else
			// no deliminer found so we initialize value as empty
			value="";

		return true;
	}

	/** Returns istream::eof().
	 * If no stream is specified, returns with true.
	 */
	bool eod()
	{
		if(!stream)
			return true;
		
		return stream->eof();
	}
};

} // namespace configuration
#endif
