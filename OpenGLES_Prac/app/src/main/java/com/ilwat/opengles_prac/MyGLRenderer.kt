package com.ilwat.opengles_prac

import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

import android.opengl.GLES20
import android.opengl.GLSurfaceView

class MyGLRenderer : GLSurfaceView.Renderer {

    override fun onSurfaceCreated(unused: GL10, config: EGLConfig) { //뷰의 OpenGL ES 환경을 설정하기 위해 한 번 호출합니다.
        // Set the background frame color
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 1.0f)
    }

    override fun onDrawFrame(unused: GL10) { //뷰를 다시 그릴 때마다 호출합니다.
        // Redraw background color
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT)
    }

    override fun onSurfaceChanged(unused: GL10, width: Int, height: Int) { //기기의 화면 방향이 변경될 때와 같이 뷰의 도형이 변경되면 호출
        GLES20.glViewport(0, 0, width, height)
    }
}
