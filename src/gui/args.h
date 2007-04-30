/*                                                                              
 * PDFedit - free program for PDF document manipulation.                        
 * Copyright (C) 2006, 2007  PDFedit team:      Michal Hocko, 
 *                                              Miroslav Jahoda,       
 *                                              Jozef Misutka, 
 *                                              Martin Petricek                                             
 *
 * Project is hosted on http://sourceforge.net/projects/pdfedit                                                                      
 */ 
#ifndef __ARGS_H__
#define __ARGS_H__
/** @file
 \brief Commandline arguments utility functions header
*/

#include <qmap.h>
#include <qstring.h>

class QStringList;

/** Name of the program (argv[0]) */
extern QString binName;

/** Option handler function */
typedef void optHandlerFn();

/** Option handler function (with parameter) */
typedef void optHandlerFnParam(const QString&);

/** Option handler function pointer*/
typedef optHandlerFn *optHandler;

/** Option handler function pointer (with parameter)*/
typedef optHandlerFnParam *optHandlerParam;

/** Option handler map*/
typedef QMap<QString, optHandler> OptionMap;

/** Option handler map (with parameter) */
typedef QMap<QString, optHandlerParam> OptionMapParam;

/** Option help map*/
typedef QMap<QString, QString> OptionHelp;

void handleHelpOptions();
void handleStopOpt();
void optionHandler(const QString &param, optHandler h,const QString &help="");
void optionHandlerParam(const QString &param, const QString &paramName, optHandlerParam h,const QString &help="");
QStringList handleParams(int _argc,char **_argv);
void appHeader();

#endif
