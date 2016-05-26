package org.cocos2dx.cpp;

/**
 * Created by arimatakeshi on 16/05/16.
 */

import android.app.Activity;
import android.content.Intent;
import android.graphics.Typeface;
import android.util.Log;
import android.view.View;
import android.widget.TextView;


public class TabActivity extends Activity{

    // タブメニュー操作
    public void tabClick(View view){
        switch (view.getId()){
            case R.id.homeBtn:
                Intent intentHome = new Intent(this, HomeActivity.class);
                startActivity(intentHome);
                break;

            case R.id.characterBtn:
                Intent intentCharacter = new Intent(this, CharacterSelectActivity.class);
                startActivity(intentCharacter);
                break;

            case R.id.settingBtn:
                Intent intentSetting = new Intent(this, SettingActivity.class);
                startActivity(intentSetting);
                break;

            case R.id.playBtn:
                Intent intentApp = new Intent(this, AppActivity.class);
                startActivity(intentApp);
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
