package org.cocos2dx.cpp;

/**
 * Created by arimatakeshi on 16/05/16.
 */

import android.app.Activity;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.content.Intent;
import android.graphics.Typeface;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.TextView;


public class MainActivity extends Activity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // タイトル消し
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_main);

    }

    // タブメニュー操作
    public void tabClick(View view){

        FragmentManager manager = getFragmentManager();
        FragmentTransaction transaction = manager.beginTransaction();

        switch (view.getId()){

            case R.id.homeBtn:
                HomeFragment homeFragment = new HomeFragment();
                transaction.replace(R.id.fragment_container,homeFragment);
                transaction.commit();

                break;

            case R.id.characterBtn:
                CharacterSelectFragment characterSelectFragment = new CharacterSelectFragment();
                transaction.replace(R.id.fragment_container,characterSelectFragment);
                transaction.commit();

                break;

            case R.id.settingBtn:
                SettingFragment settingFragment = new SettingFragment();
                transaction.replace(R.id.fragment_container,settingFragment);
                transaction.commit();
                break;

            default:
                break;

        }
    }

    /*
    * フォントタイプ指定
    * setFontType()
    */
    public void setFontType(TextView txt) {
        txt.setTypeface(Typeface.createFromAsset(getAssets(), "fonts/logotypejp_mp_m_1.1.ttf"));
    }

    @Override
    protected void onStop() {
        super.onStop();
        // TODO 閉じる時に音を消す処理
        Log.i("tabactivity", "閉じたよー");
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        // TODO 閉じる時に音を消す処理
        Log.i("tabactivity", "閉じたよーdestory");
    }
}
