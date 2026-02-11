/* 
 * File:   fileManagement.h
 * Author: alejandro
 *
 * Created on January 25, 2012, 10:34 PM
 */

#include<string>
#include<map>
#ifndef FILEMANAGEMENT_H
#define	FILEMANAGEMENT_H

std::string loadfile(char*);

std::map<std::string, double> loadConfiguration(char*);


#endif	/* FILEMANAGEMENT_H */

