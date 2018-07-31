#include "cmake_build.h"

QString cmake_build::exec_name;

cmake_build::cmake_build()
{

}

QString cmake_build::cmake_minimum_required(QString version)
{
    return QString::fromLocal8Bit("cmake_minimum_required")+QString::fromLocal8Bit("(")+version+QString::fromLocal8Bit(")");
}
QString cmake_build::project(QString project_name)
{

    exec_name = project_name;
    return QString::fromLocal8Bit("project")+QString::fromLocal8Bit("(")+project_name+QString::fromLocal8Bit(")");
}

QString cmake_build::add_executable(QString exec,QString source_dir,cmake_type type)
{
    return SetDoubleParameter("add_executable",exec,source_dir,type);
}

QString cmake_build::aux_source_directory(QString dir, QString source_dir,cmake_type type)
{
   return SetDoubleParameter("aux_source_directory",dir,source_dir,type);

}

QString cmake_build::include_directories(QString include_dir,cmake_type type)
{
    return SetOneParameter("include_directories",include_dir,type);
}

QString cmake_build::link_directories(QString dir,cmake_type type)
{
    return SetOneParameter("link_directories",dir,CMAKE_ARGV);
}

QString cmake_build::set(QString argv,QString dir,cmake_type type)
{
    return SetDoubleParameter("set",argv,dir,type);
}

QString cmake_build::target_link_libraries(QString current_dir,QString lib_name,cmake_type type)//argv1 depend argv2 (lib)
{
    int index = current_dir.lastIndexOf("/");
    QString exec_name = current_dir.right(current_dir.length() - index - 1);

    int index2 = lib_name.lastIndexOf("/");
    QString lib_name2 = lib_name.right(lib_name.length() - index2 - 1);
    return SetDoubleParameter("target_link_libraries",exec_name,lib_name2,type);
}

QString cmake_build::add_subdirectory(QString dir,cmake_type type)
{
    return SetOneParameter("add_subdirectory",dir,type);
}

QString cmake_build::add_library(QString current_dir,QString source_dir,enum cmake_type type1,enum lib_type type2)
{
    int index = current_dir.lastIndexOf("/");
    QString lib_name = current_dir.right(current_dir.length() - index - 1);
    qDebug()<<"TTTTTTTTTTTTTTTTTTTTTTTTTTTTTT"<<type2;

    if(type2 == STATIC)
        return SetTribleParameter("add_library",lib_name,source_dir,type1,"STATIC");
    else if(type2 == SHARED)
        return SetTribleParameter("add_library",lib_name,source_dir,type1,"SHARED");
}



QString cmake_build::SourceDir(QString root_dir)
{
    QString source_dir = root_dir;
    return source_dir;
}

QString cmake_build::IncludeDir(QString root_dir)
{
    QString include_dir = root_dir;
    return include_dir;
}

QString cmake_build::SetTribleParameter(QString options,QString Parameter1,QString Parameter2,cmake_type type1,QString lib_type)
{
    if(type1 == 0)//string
        return options +QString::fromLocal8Bit("(")+Parameter1 + " " + lib_type + " " + Parameter2+QString::fromLocal8Bit(")");
    else if(type1 == 1)
        return options +QString::fromLocal8Bit("(")+Parameter1 + " " + lib_type + " " + "$" +"{" + Parameter2 + "}" + QString::fromLocal8Bit(")");
}

//template <class type>
QString cmake_build::SetDoubleParameter(QString options , QString Parameter1, QString Parameter2, cmake_type type)
{
    if(type == 0)//string
        return options +QString::fromLocal8Bit("(")+Parameter1 + " " + Parameter2+QString::fromLocal8Bit(")");
    else if(type == 1)
        return options +QString::fromLocal8Bit("(")+Parameter1 + " " + "$" +"{" + Parameter2 + "}" + QString::fromLocal8Bit(")");
}

QString cmake_build::SetOneParameter(QString options, QString Parameter1, cmake_type type)
{
    if(type == 1)//argv
        return options + "(${" + Parameter1 + "})";
    else if(type == 0)
        return options + "(" + Parameter1 + ")";
}


