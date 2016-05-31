package org.cocos2dx.cpp;

import android.app.Activity;
import android.app.Fragment;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;

import java.io.IOException;


public class HomeFragment extends Fragment {

    private ImageButton playBtn;

    private MainActivity activity;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_home,container,false);
    }

    @Override
    public void onStart() {
        super.onStart();

        // アクティビティのメソッドを使うためにインスタンス化
        activity = (MainActivity)getActivity();

        // playボタン（キャラクターの画像）のインスタンス化
        playBtn = (ImageButton)activity.findViewById(R.id.playBtn);

        // playボタンが押された時の処理
        playBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intentApp = new Intent(activity, AppActivity.class);
                startActivity(intentApp);
            }
        });
    }

    @Override
    public void onResume() {
        super.onResume();

        // キャラクターの画像を変更する
        changeCharacter();
    }

    public void changeCharacter(){
        // ユーザが選択していたキャラクターを取得
        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(activity);
        int currentCharaNo =preferences.getInt("current_character_no", 1);
        CharacterData currentCharacter = activity.characterDataList.get(currentCharaNo - 1);

        // playボタンの画像を変更
        try {
            Bitmap bitmap = activity.loadBitmapFromAsset(currentCharacter.getImage_stand());
            BitmapDrawable bitmapDrawable = new BitmapDrawable(getResources(), bitmap);
            playBtn.setBackground(bitmapDrawable);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
