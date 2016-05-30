package org.cocos2dx.cpp;

import android.app.Fragment;
import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Bundle;
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

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_setting,container,false);
    }

    @Override
    public void onStart() {
        super.onStart();

        // アクティビティのメソッドを使うためにインスタンス化
        MainActivity activity = (MainActivity) getActivity();

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


        // ボリューム取得
        final SeekBar vol = (SeekBar)activity.findViewById(R.id.volumeBar);

        AudioManager am = (AudioManager)activity.getSystemService(Context.AUDIO_SERVICE);

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
                        AudioManager am = (AudioManager)getActivity().getSystemService(Context.AUDIO_SERVICE);
                        am.setStreamVolume(AudioManager.STREAM_MUSIC, seekBar.getProgress(), 0);
                    }
                }
        );

        ToggleButton s = (ToggleButton)activity.findViewById(R.id.bgmSwitch);

        if (s != null) {
            s.setOnCheckedChangeListener(new OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton buttonView,
                                             boolean isChecked) {
                    // サービスクラスを指定
                    intentBgm = new Intent(getActivity(), BgmService.class);

                    if(isChecked) {
                        //do stuff when Switch is ON
                        Log.i("debug","開始");
                        getActivity().startService(intentBgm);


                    } else {
                        //do stuff when Switch if OFF
                        Log.i("debug","停止");
                        getActivity().stopService(intentBgm);

                    }
                }
            });
        }

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
