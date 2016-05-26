package org.cocos2dx.cpp;

import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.ToggleButton;

public class SettingActivity extends TabActivity {

    private Intent intentBgm = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_setting);


        // フォント変更
        TextView txt = (TextView) findViewById(R.id.volumeLbl);
        setFontType(txt);

        // フォント変更
        TextView optTxt = (TextView) findViewById(R.id.optionText);
        setFontType(optTxt);

        // フォント変更
        TextView bgmTxt = (TextView) findViewById(R.id.bgmTxt);
        setFontType(bgmTxt);

        // フォント変更
        TextView seTxt = (TextView) findViewById(R.id.seTxt);
        setFontType(seTxt);


        // ボリューム取得
        final SeekBar vol = (SeekBar)findViewById(R.id.volumeBar);

        AudioManager am = (AudioManager)getSystemService(Context.AUDIO_SERVICE);

        // 初期値
        vol.setProgress(am.getStreamVolume(AudioManager.STREAM_MUSIC));
        // 最大値
        vol.setMax(15);

        // シークバーコントロール
        vol.setOnSeekBarChangeListener(
                new SeekBar.OnSeekBarChangeListener() {
                    public void onProgressChanged(SeekBar seekBar,
                                                  int progress, boolean fromUser) {
                    }

                    public void onStartTrackingTouch(SeekBar seekBar) {
                        // ツマミに触れたときに呼ばれる
                    }

                    public void onStopTrackingTouch(SeekBar seekBar) {
                        // ツマミを離したときに呼ばれる
                        Log.i("debug","out" + seekBar.getProgress());
                        AudioManager am = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
                        am.setStreamVolume(AudioManager.STREAM_MUSIC, seekBar.getProgress(), 0);
                    }
                }
        );

        ToggleButton s = (ToggleButton) findViewById(R.id.bgmSwitch);

        if (s != null) {
            s.setOnCheckedChangeListener(new OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton buttonView,
                                             boolean isChecked) {
                    // サービスクラスを指定
                    intentBgm = new Intent(SettingActivity.this, BgmService.class);

                    if(isChecked) {
                        //do stuff when Switch is ON
                        Log.i("debug","開始");
                        startService(intentBgm);


                    } else {
                        //do stuff when Switch if OFF
                        Log.i("debug","停止");
                        stopService(intentBgm);

                    }
                }
            });
        }
    }

    // ボタン操作
    public void onClick(View view){
        switch (view.getId()){

            case R.id.sitelink:
                Uri uri = Uri.parse("https://www.google.co.jp");
                Intent i = new Intent(Intent.ACTION_VIEW, uri);
                startActivity(i);
                break;

        }
    }


}
