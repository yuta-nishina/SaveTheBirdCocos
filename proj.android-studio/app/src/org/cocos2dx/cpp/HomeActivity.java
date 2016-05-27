package org.cocos2dx.cpp;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;


public class HomeActivity extends TabActivity {

    @Override
    // 初期表示
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // タイトル消し
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_home);
    }

    // ボタン操作
    public void onClick(View view){
        switch (view.getId()){

            case R.id.playBtn:
                Intent intentApp = new Intent(this, AppActivity.class);
                startActivity(intentApp);
                break;
        }
    }
}
