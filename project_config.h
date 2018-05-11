#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H



enum ERootLibType
{
    ROOT_LIB_STATIC=1,
    ROOT_LIB_SHARED,
    ROOT_LIB_NONE
};

enum ESubLibType
{
    SUB_LIB_STATIC=1,
    SUB_LIB_SHARED,
};

enum ERootProjectType
{
    EXEC=1,
    LIB,
};




struct SProjcetConfig
{
    ERootProjectType project_type;
    enum ERootLibType root_lib_type;
    enum ESubLibType sub_lib_type;
};





#endif // PROJECT_CONFIG_H
