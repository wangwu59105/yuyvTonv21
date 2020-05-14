package com.sf.nv.utils;

public class Yuyv {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("nv-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void YuyvToNv21_Char(byte[] nv21, int with, int height, byte[] yuy2);

    public native void YuyvToNv21(byte[] yuy2, int with, int height, byte[] nv21);


    public byte[] yuyv2nv21(byte[] yuyv, int width, int height) {
        int yuyvSize = width * height * 2;
        int nv21Size = width * height * 3 / 2;
        byte[] nv21 = new byte[nv21Size];
        int y = 0, v = width * height, u = v + 1;
        for (int i = 0; i < yuyvSize; i += 4) {
            nv21[y++] = yuyv[i];//y
            nv21[y++] = yuyv[i + 2];//y
        }
        int h, j;
        boolean isu = true;
        for (h = 0; h < height; h += 2) {
            int baseh = h * width * 2;
            for (j = baseh + 1; j < baseh + width * 2; j += 2) {
                if (isu) {
                    nv21[u] = yuyv[j];
                    u += 2;
                    isu = false;
                } else {
                    nv21[v] = yuyv[j];
                    v += 2;
                    isu = true;
                }
            }
        }
        return nv21;
    }

}
