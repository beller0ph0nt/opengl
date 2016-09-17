int
main()
{

    /*

    glGenTextures(1, texID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    #if 0 //===> It's OK     ----------------glTexImage2d case OK---------------------

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, img_width, img_height,0,GL_RGB,GL_UNSIGNED_BYTE,imgBuf)

    #else //===> it's not OK  ----------------eglimage case Fail---------------------

    //set teximage
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, img_width, img_height,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);

    //create
    eglimage = eglCreateImageKHR( pStatics->sEGLInfo.sEGLDisplay, pStatics->sEGLInfo.sEGLContext,
        EGL_GL_TEXTURE_2D_KHR, (EGLClientBuffer) texID[0], NULL);

    //update eglimage data from texture data
    EGLint attribs_rgb[] =
    {
      MALI_EGL_IMAGE_PLANE, MALI_EGL_IMAGE_PLANE_RGB,
      MALI_EGL_IMAGE_MIPLEVEL, 0,
      MALI_EGL_IMAGE_ACCESS_MODE, MALI_EGL_IMAGE_ACCESS_READ_WRITE,
      EGL_NONE
    };

    mali_egl_image *img = mali_egl_image_lock_ptr( eglimage );
    void *rgb = mali_egl_image_map_buffer( img, attribs_rgb );


    // необходимо определить формат, в котором у текстуры храниться буффер.
    // на своем личном опыте сталкивался с форматом BGRA8888.
    // так же возмжно необходимо будет воспользоваться малишной ф-ией по созданию eglimage-а.
    // поэтому копирование скорее всего будет осуществляться через MEMCPY( bgrf, pdata, width*height*  4  );

    MEMCPY( rgb, pdata, width*height*3);

    mali_egl_image_unmap_buffer( img, attribs_rgb );

    //connect eglimage to texture
    glEGLImageTargetTexture2DOES( GL_TEXTURE_2D, (GLeglImageOES)eglImage);

    //destroy
    eglDestroyImageKHR(pStatics->sEGLInfo.sEGLDisplay, eglImage);

    */


    // еще один пример кода

    /*

    glGenTextures(1, texID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID[0]);
    ...
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, img_width, img_height,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
    ...
    eglimage = eglCreateImageKHR( pStatics->sEGLInfo.sEGLDisplay, pStatics->sEGLInfo.sEGLContext, EGL_GL_TEXTURE_2D_KHR, (EGLClientBuffer) texID[0], NULL);

    EGLint attribs_rgb[] =
    {
      MALI_EGL_IMAGE_PLANE, MALI_EGL_IMAGE_PLANE_RGB,
      MALI_EGL_IMAGE_MIPLEVEL, 0,
      MALI_EGL_IMAGE_ACCESS_MODE, MALI_EGL_IMAGE_ACCESS_READ_WRITE,
      EGL_NONE
    };

    mali_egl_image *img = mali_egl_image_lock_ptr( eglimage ); //<--- вот здесь начинаются чудеса
    void *rgb = mali_egl_image_map_buffer( img, attribs_rgb );
    MEMCPY( rgb, pdata, width*height*3);
    mali_egl_image_unmap_buffer( img, attribs_rgb );

    */




    return 0;
}