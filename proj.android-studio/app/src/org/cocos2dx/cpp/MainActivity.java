package org.cocos2dx.cpp;

/**
 * Created by arimatakeshi on 16/05/16.
 */

import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.graphics.Typeface;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.TextView;


public class MainActivity extends Activity{

    private HomeFragment homeFragment;
    private CharacterSelectFragment characterSelectFragment;
    private SettingFragment settingFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // タイトル消し
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_main);

    }

    @Override
    protected void onStart() {
        super.onStart();

        // フラグメントの初期化
        FragmentManager manager = getFragmentManager();
        FragmentTransaction transaction = manager.beginTransaction();
        if (homeFragment == null){
            homeFragment = new HomeFragment();
        }
        if (characterSelectFragment == null){
            characterSelectFragment = new CharacterSelectFragment();
        }
        if (settingFragment == null){
            settingFragment = new SettingFragment();
        }

        // フラグメントをViewに追加
        Fragment currentFragment = manager.findFragmentById(R.id.fragment_container);

        if (currentFragment == null){
            transaction.add(R.id.fragment_container,homeFragment);
            transaction.add(R.id.fragment_container,characterSelectFragment);
            transaction.add(R.id.fragment_container,settingFragment);

            transaction.hide(characterSelectFragment);
            transaction.hide(settingFragment);
            transaction.show(homeFragment);
        }
        transaction.commit();
    }

    // タブメニュー操作
    public void tabClick(View view){

        FragmentManager manager = getFragmentManager();
        FragmentTransaction transaction = manager.beginTransaction();

        switch (view.getId()){

            case R.id.homeBtn:
                transaction.hide(characterSelectFragment);
                transaction.hide(settingFragment);
                transaction.show(homeFragment);
                break;

            case R.id.characterBtn:
                transaction.hide(homeFragment);
                transaction.hide(settingFragment);
                transaction.show(characterSelectFragment);
                break;

            case R.id.settingBtn:
                transaction.hide(homeFragment);
                transaction.hide(characterSelectFragment);
                transaction.show(settingFragment);
                break;

            default:
                break;

        }
        transaction.commit();
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
