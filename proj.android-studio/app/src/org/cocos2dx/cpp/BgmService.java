package org.cocos2dx.cpp;

import android.app.Service;
import android.content.Intent;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.IBinder;
import android.util.Log;

public class BgmService extends Service {

    private MediaPlayer player;

    @Override
    public IBinder onBind(Intent intent) {
        // TODO Auto-generated method stub
        return null;
    }

    // 開始時にコール
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        // TODO Auto-generated method stub
        super.onStart(intent, startId);
        Log.i("service", "BGM開始");

        // 再生中なら停止
        if (player != null && player.isPlaying()) {
            player.stop(); // 停止
            player.release();// メモリの解放
        }
        // 再生
        try {
            player = MediaPlayer.create(this, R.raw.sample);
            player.setAudioStreamType(AudioManager.STREAM_MUSIC);
            player.setLooping(true);  // 連続再生設定
            player.start(); // 再生

        } catch (IllegalArgumentException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        return super.onStartCommand(intent, flags, startId);
    }

    // 終了時にコール
    @Override
    public void onDestroy() {
        // TODO Auto-generated method stub
        super.onDestroy();
        Log.i("service", "BGM停止");
        player.stop();
        player.release();
        Log.i("service", "BGM停止完了");
    }
}