#ifndef CMAKE_BUILD_H
#define CMAKE_BUILD_H

#include <QString>
#include <QDebug>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>

enum cmake_type
{
  CMAKE_STRING = 0,
  CMAKE_ARGV = 1

};
enum lib_type
{
    STATIC = 5,
    SHARED
};

class cmake_build
{
public:
    cmake_build();

    static QString project(QString current_dir);
    static QString aux_source_directory(QString dir, QString source_dir, cmake_type type);
    static QString set(QString argv, QString dir, cmake_type type);
    static QString include_directories(QString include_dir, cmake_type type);
    static QString add_executable(QString exec, QString source_dir, cmake_type type);
    static QString link_directories(QString dir, cmake_type type);
    static QString target_link_libraries(QString current_dir, QString lib_name, cmake_type type);

    static QString SourceDir(QString root_dir);
    static QString IncludeDir(QString include_dir);
    static QString add_subdirectory(QString dir, cmake_type type);
    static QString add_library(QString current_dir, QString source_dir, enum cmake_type type1, lib_type type2);
    //template <class type>
    static QString SetTribleParameter(QString options,QString Parameter1,QString Parameter2,cmake_type type1,QString lib_type);
    static QString SetDoubleParameter(QString options, QString Parameter1, QString Parameter2, enum cmake_type type);
    static QString SetOneParameter(QString options, QString Parameter1, cmake_type type);

};



#endif // CMAKE_BUILD_H
