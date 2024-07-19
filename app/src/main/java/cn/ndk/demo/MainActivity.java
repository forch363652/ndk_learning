package cn.ndk.demo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import cn.ndk.demo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'demo' library on application startup.
    static {
        System.loadLibrary("demo");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String pkgName =  test(getBaseContext());
        Log.i("test_log", "so执行结果："+pkgName);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(input("输入什么，jni返回什么："));
        stringFromJNI();
    }

    public native String stringFromJNI();

    public native String input(String input);

    //public native String nlog(String str);

    public native String test(Context context);

    // Used to load the 'native-lib' library on application startup.

}