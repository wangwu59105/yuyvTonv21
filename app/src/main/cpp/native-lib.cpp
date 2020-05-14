#include <jni.h>
#include <string>


void NV21_2_YUY2(jbyte *src, jbyte *dst, int width, int height) {
    int size = width * height;
    jbyte *pSrcUV = src + size;
    for (int i = 0; i < size; ++i) {
        dst[i * 2] = src[i];
    }
    int p1 = 0;
    int vPos = 0;
    for (int y = 0; y < height; ++y) {
        //int vPos = y/2*width;
        if (y % 2 != 0) {
            vPos -= width;
        }
        for (int x = 0; x < width / 2; ++x) {
            int uPos = vPos + 1;
            int p2 = p1 + 2;//yv point
            dst[p1 + 1] = pSrcUV[uPos];
            dst[p2 + 1] = pSrcUV[vPos];
            vPos += 2;
            p1 += 4;
        }
    }
}

void YUY2_2_NV21(jbyte *src, jbyte *dst, int width, int height) {
    jbyte *pDstY = dst;
    jbyte *pDstUV = dst + width * height;
    int halfH = height / 2;
    int halfW = width / 2;
    int stride = width * 2;
    int p1, p2, p3, p4;
    int index = 0;
    for (int y = 0; y < halfH; ++y) {
        for (int x = 0; x < halfW; ++x) {
            //int px = 2*x;
            //int py = 2*y;
            //int index = py*stride + px*2;
            p1 = (index);
            p2 = (index) + 2;
            p3 = (index) + stride;
            p4 = (index) + stride + 2;
            pDstUV[y * width + x * 2] = static_cast<char>((src[p2 + 1] + src[p4 + 1]) / 2);
            pDstUV[y * width + x * 2 + 1] = static_cast<char>((src[p1 + 1] + src[p3 + 1]) / 2);
            pDstY[p1 >> 1] = src[p1];
            pDstY[p2 >> 1] = src[p2];
            pDstY[p3 >> 1] = src[p3];
            pDstY[p4 >> 1] = src[p4];
            index += 4;
        }
        index += stride;
    }
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_sf_nv_utils_Yuyv_stringFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement stringFromJNI()
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



extern "C"
JNIEXPORT void JNICALL
Java_com_sf_nv_utils_Yuyv_YuyvToNv21(JNIEnv *env, jobject thiz, jbyteArray yuy2, jint with,
                                     jint height, jbyteArray nv21) {
    // TODO: implement YuyvToNv21()
    jsize size_nv21 = with * height * 3 / 2;
    jbyte *src_yuy2_data = env->GetByteArrayElements(yuy2, NULL);
    jbyte *dst_nv21_data = env->GetByteArrayElements(nv21, NULL);
    YUY2_2_NV21(src_yuy2_data, dst_nv21_data, with, height);
    //env->SetByteArrayRegion(nv21, 0, size_nv21, dst_nv21_data);
    env->ReleaseByteArrayElements(yuy2, src_yuy2_data, 0);
    env->ReleaseByteArrayElements(nv21, dst_nv21_data, 0);


}


char *ConvertJByteaArrayToChars(JNIEnv *env, jbyteArray bytearray) {
    char *chars = NULL;
    jbyte *bytes;
    bytes = env->GetByteArrayElements(bytearray, 0);
    int chars_len = env->GetArrayLength(bytearray);
    chars = new char[chars_len + 1];
    memset(chars, 0, chars_len + 1);
    memcpy(chars, bytes, chars_len);
    chars[chars_len] = 0;

    env->ReleaseByteArrayElements(bytearray, bytes, 0);

    return chars;
}

void NV21_2_YUY2_Char(char *src, char *dst, int width, int height) {
    int size = width * height;
    char *pSrcUV = src + size;
    for (int i = 0; i < size; ++i) {
        dst[i * 2] = src[i];
    }
    int p1 = 0;
    int vPos = 0;
    for (int y = 0; y < height; ++y) {
        //int vPos = y/2*width;
        if (y % 2 != 0) {
            vPos -= width;
        }
        for (int x = 0; x < width / 2; ++x) {
            int uPos = vPos + 1;
            int p2 = p1 + 2;//yv point
            dst[p1 + 1] = pSrcUV[uPos];
            dst[p2 + 1] = pSrcUV[vPos];
            vPos += 2;
            p1 += 4;
        }
    }
}

void YUY2_2_NV21_Char(char *src, char *dst, int width, int height) {
    char *pDstY = dst;
    char *pDstUV = dst + width * height;
    int halfH = height / 2;
    int halfW = width / 2;
    int stride = width * 2;
    int p1, p2, p3, p4;
    int index = 0;
    for (int y = 0; y < halfH; ++y) {
        for (int x = 0; x < halfW; ++x) {
            //int px = 2*x;
            //int py = 2*y;
            //int index = py*stride + px*2;
            p1 = (index);
            p2 = (index) + 2;
            p3 = (index) + stride;
            p4 = (index) + stride + 2;
            pDstUV[y * width + x * 2] = (src[p2 + 1] + src[p4 + 1]) / 2;
            pDstUV[y * width + x * 2 + 1] = (src[p1 + 1] + src[p3 + 1]) / 2;
            pDstY[p1 >> 1] = src[p1];
            pDstY[p2 >> 1] = src[p2];
            pDstY[p3 >> 1] = src[p3];
            pDstY[p4 >> 1] = src[p4];
            index += 4;
        }
        index += stride;
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_sf_nv_utils_Yuyv_YuyvToNv21_1Char(JNIEnv *env, jobject thiz, jbyteArray yuy2, jint with,
                                           jint height, jbyteArray nv21) {
    // TODO: implement YuyvToNv21_Char()
    jsize size_nv21 = with * height * 3 / 2;
    char *src_yuy2_data = ConvertJByteaArrayToChars(env, yuy2);
    char *dst_nv21_data  = new char[size_nv21 + 1];
    dst_nv21_data[size_nv21] = 0;
    YUY2_2_NV21_Char(src_yuy2_data, dst_nv21_data, with, height);

    jbyte *outbuff = env->GetByteArrayElements(nv21, JNI_FALSE);
    memcpy(outbuff, dst_nv21_data, static_cast<size_t>(size_nv21));
    env->SetByteArrayRegion(nv21, 0, size_nv21, outbuff);
    env->ReleaseByteArrayElements(nv21, outbuff, JNI_OK);
    delete src_yuy2_data;
    delete dst_nv21_data;
}