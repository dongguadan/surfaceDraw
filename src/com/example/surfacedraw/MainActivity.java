package com.example.surfacedraw;

import android.app.Activity;  
import android.graphics.Canvas;  
import android.graphics.Color;  
import android.graphics.Paint;  
import android.graphics.Rect;

import android.os.Bundle;
import android.view.Surface;
import android.view.SurfaceHolder;  
import android.view.SurfaceView;  


public class MainActivity extends Activity {
	public native String  native_stringFromJNI();
	public native String  native_avcodecregisteral();
	public native String  native_avregisteral();
	public native String  native_init();
	public native String  native_setup();
	public native String  native_release();
	public native String  native_setDataSource(String path);
	public native String  native_setVideoSurface(Surface surface);
	public native String  native_prepare();
	public native String  native_start();
	public native String  native_stop();
	
	private SurfaceView    sf;      
    private SurfaceHolder  sfh;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		sf = (SurfaceView) this.findViewById(R.id.show);  
        sfh = sf.getHolder();  
        sfh.addCallback(new DoThings());
	}
    
    static {
        System.loadLibrary("jniaudio");
        System.loadLibrary("jnivideo");
        System.loadLibrary("ffmpeg-jni");
    }
	
    private class DoThings implements SurfaceHolder.Callback{  
        @Override  
        public void surfaceChanged(SurfaceHolder holder, int format, int width,  
                int height) {  
            System.out.println("surfaceChanged...");
            System.out.println(native_start());
        }  
  
        @Override  
        public void surfaceCreated(SurfaceHolder holder){
            System.out.println("surfaceCreated...");
        	System.out.println(native_avcodecregisteral());
        	System.out.println(native_avregisteral());
        	System.out.println(native_init());
        	System.out.println(native_setup());
        	System.out.println(native_setDataSource("/sdcard/SDVideo1.avi"));
        	System.out.println(native_setVideoSurface(sfh.getSurface()));
        	System.out.println(native_prepare());
        }  
  
        @Override  
        public void surfaceDestroyed(SurfaceHolder holder) {  
            System.out.println("surfaceDestroyed=="); 
            System.out.println(native_stop());
            System.out.println(native_stringFromJNI());
        }     
    }
	
}
