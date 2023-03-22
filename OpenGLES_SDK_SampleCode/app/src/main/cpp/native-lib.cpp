//#include <jni.h>
//#include <string>
//
//extern "C" JNIEXPORT jstring JNICALL
//Java_com_ilwat_opengles_1sdk_1samplecode_MainActivity_stringFromJNI(
//        JNIEnv* env,
//        jobject /* this */) {
//    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
//}

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <GLES/gl.h>
#include <GLES/glext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
/* [Includes] */

/* [Vertex source] */
static const char glVertexShader[] =
        "attribute vec4 vPosition;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = vPosition;\n"
        "}\n";
/* [Vertex source] */

/* [Fragment source] */
static const char glFragmentShader[] =
        "precision mediump float;\n"
        "void main()\n"
        "{\n"
        "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";
/* [Fragment source] */

/* [loadShader] */
GLuint loadShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader)
    {
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen)
            {
                char * buf = (char*) malloc(infoLen);

                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not Compile Shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}
/* [loadShader] */

/* [createProgram] */
GLuint createProgram(const char* vertexSource, const char * fragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader)
    {
        return 0;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader)
    {
        return 0;
    }

    GLuint program = glCreateProgram();

    if (program)
    {
        glAttachShader(program , vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;

        glGetProgramiv(program , GL_LINK_STATUS, &linkStatus);

        if( linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;

            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);

            if (bufLength)
            {
                char* buf = (char*) malloc(bufLength);

                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }

    return program;
}
/* [createProgram] */

/* [setupGraphics] */
GLuint simpleTriangleProgram;
GLuint vPosition;

bool setupGraphics(int w, int h)
{
    simpleTriangleProgram = createProgram(glVertexShader, glFragmentShader);

    if (!simpleTriangleProgram)
    {
        LOGE ("Could not create program");
        return false;
    }

    vPosition = glGetAttribLocation(simpleTriangleProgram, "vPosition");

    glViewport(0, 0, w, h);

    return true;
}
/* [setupGraphics] */

/* [renderFrame] */
const GLfloat triangleVertices[] = {
        0.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f
};

void renderFrame()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(simpleTriangleProgram);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0 ,triangleVertices);
    glEnableVertexAttribArray(vPosition);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
/* [renderFrame] */

extern "C"
{
JNIEXPORT void JNICALL Java_com_ilwat_opengles_1sdk_1samplecode_NativeLibrary_init(
        JNIEnv * env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_ilwat_opengles_1sdk_1samplecode_NativeLibrary_step(
        JNIEnv * env, jobject obj);
};

/* [Native functions] */
JNIEXPORT void JNICALL Java_com_ilwat_opengles_1sdk_1samplecode_NativeLibrary_init(
        JNIEnv * env, jobject obj, jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_ilwat_opengles_1sdk_1samplecode_NativeLibrary_step(
        JNIEnv * env, jobject obj)
{
    renderFrame();
}
/* [Native functions] */