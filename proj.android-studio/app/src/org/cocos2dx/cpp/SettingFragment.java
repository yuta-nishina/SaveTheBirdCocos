package org.cocos2dx.cpp;

import android.app.Fragment;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.ToggleButton;

public class SettingFragment extends Fragment {

    private Intent intentBgm = null;

    private MainActivity activity;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_setting,container,false);
    }

    @Override
    public void onStart() {
        super.onStart();

        // アクティビティのメソッドを使うためにインスタンス化
        activity = (MainActivity) getActivity();

        // フォント変更
        TextView txt = (TextView)activity.findViewById(R.id.volumeLbl);
        activity.setFontType(txt);

        // フォント変更
        TextView optTxt = (TextView)activity.findViewById(R.id.optionText);
        activity.setFontType(optTxt);

        // フォント変更
        TextView bgmTxt = (TextView)activity.findViewById(R.id.bgmTxt);
        activity.setFontType(bgmTxt);

        // フォント変更
        TextView seTxt = (TextView)activity.findViewById(R.id.seTxt);
        activity.setFontType(seTxt);


        // ボリュームのシークバーをインスタンス化
        final SeekBar vol = (SeekBar)activity.findViewById(R.id.volumeBar);

        // AudioManagerを取得
        AudioManager am = (AudioManager)activity.getSystemService(Context.AUDIO_SERVICE);

        // 初期値
        final SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(activity);
        vol.setProgress(preferences.getInt("volume",8)); // 設定されていない場合（初期値）= 8
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
                        AudioManager am = (AudioManager)activity.getSystemService(Context.AUDIO_SERVICE);
                        am.setStreamVolume(AudioManager.STREAM_MUSIC, seekBar.getProgress(), 0);

                        // 設定値を更新
                        preferences.edit().putInt("volume",seekBar.getProgress()).apply();
                    }
                }
        );

        // BGMのスイッチをインスタンス化
        ToggleButton bgmToggleButton = (ToggleButton)activity.findViewById(R.id.bgmSwitch);
        // 初期状態（ONかOFFか）を設定
        bgmToggleButton.setChecked(preferences.getBoolean("bgm_flg", true)); // 設定されていない場合はtrue(ON)

        // BGMのスイッチが変更された時の処理
        bgmToggleButton.setOnCheckedChangeListener(new OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView,
                                         boolean isChecked) {
                // サービスクラスを指定
                intentBgm = new Intent(activity, BgmService.class);

                if(isChecked) {
                    //do stuff when Switch is ON
                    Log.i("debug","開始");
                    activity.startService(intentBgm);
                } else {
                    //do stuff when Switch if OFF
                    Log.i("debug","停止");
                    activity.stopService(intentBgm);
                }

                // 設定値を更新
                SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(activity);
                preferences.edit().putBoolean("bgm_flg",isChecked).apply();
            }
        });

        // SEのスイッチをインスタンス化
        ToggleButton seToggleButton = (ToggleButton)activity.findViewById(R.id.seSwitch);
        // 初期状態（ONかOFFか）を設定
        seToggleButton.setChecked(preferences.getBoolean("se_flg", true)); // 設定されていない場合はtrue(ON)
        // SEのスイッチが変更された時の処理
        seToggleButton.setOnCheckedChangeListener(new OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView,
                                         boolean isChecked) {
                // 設定値を更新
                SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(activity);
                preferences.edit().putBoolean("se_flg",isChecked).apply();
            }
        });

        // 公式リンクボタンが押された時の処理
        Button siteLinkButton = (Button)activity.findViewById(R.id.sitelink);
        siteLinkButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Uri uri = Uri.parse("https://www.google.co.jp");
                Intent i = new Intent(Intent.ACTION_VIEW, uri);
                startActivity(i);
            }
        });
    }
}
