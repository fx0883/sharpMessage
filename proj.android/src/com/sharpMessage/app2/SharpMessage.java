
package com.sharpMessage.app2;

import org.CrossApp.lib.Cocos2dxActivity;
import org.CrossApp.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;
import android.view.KeyEvent;
import android.widget.Toast;

public class SharpMessage extends BaseActivity{
	
    public void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// SharpMessage should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("CrossApp_cpp");
    }  
    
	private long mkeyTime = 0;
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
	    //二次返回退出
	    if (keyCode == KeyEvent.KEYCODE_BACK) {
	        if ((System.currentTimeMillis() - mkeyTime) > 2000) {
	            mkeyTime = System.currentTimeMillis();
	            Toast.makeText(this,com.sharpMessage.app2.R.string.exit_hint, Toast.LENGTH_LONG).show();
	        } else {
	            finish();
	            System.exit(0);
	        }
	        return false;
	    }
	    return super.onKeyDown(keyCode, event);
	}
	
	@Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        if (event.getKeyCode() == KeyEvent.KEYCODE_BACK) {
        	
        	if (event.getAction() == KeyEvent.ACTION_DOWN && event.getRepeatCount() == 0) 
        	{
	        if ((System.currentTimeMillis() - mkeyTime) > 2000) 
	        {
	            mkeyTime = System.currentTimeMillis();
	            Toast.makeText(this,com.sharpMessage.app2.R.string.exit_hint, Toast.LENGTH_LONG).show();

	        } 
	        else 
	        {
	            finish();
	            System.exit(0);
	        }
        	}
	        return true;
        }
        return super.dispatchKeyEvent(event);
    }
}
