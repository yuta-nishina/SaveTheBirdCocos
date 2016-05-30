package org.cocos2dx.cpp;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Typeface;
import android.os.Bundle;
import android.os.Handler;
import android.view.Window;
import android.widget.TextView;


public class LaunchActivity extends Activity {

    @Override
    // 初期表示
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // タイトル消し
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_launch);

        // フォント変更
        TextView txt = (TextView) findViewById(R.id.splashLogo);
        txt.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/logotypejp_mp_m_1.1.ttf"));

        // スプラッシュ
        Handler handler = new Handler();
        handler.postDelayed(new splashHandler(), 3000);
    }

    // 自動画面遷移
    class splashHandler implements Runnable {
        public void run() {
            Intent intentNext = new Intent(getApplication(), MainActivity.class);
            startActivity(intentNext);
            LaunchActivity.this.finish();
        }
    }

}
