#ifndef _SHADER_SRC_H_
#define _SHADER_SRC_H_

#define SHADER_CODE(...) #__VA_ARGS__

enum shader_id
{
    SHADOW_MAP_VS_SOURCE,
    SHADOW_MAP_FS_SOURCE,
    IMAGE_VS_SOURCE,
    POINTLIGHT_FS_SOURCE,
    AREALIGHT_FS_SOURCE,
};

const char *get_shader(shader_id id);

#endif //_SHADER_SRC_H_