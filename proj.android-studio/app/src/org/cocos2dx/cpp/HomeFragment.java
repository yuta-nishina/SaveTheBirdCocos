package org.cocos2dx.cpp;

import android.app.Fragment;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.Button;
import android.widget.ImageButton;


public class HomeFragment extends Fragment {

    private ImageButton playBtn;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_home,container,false);
    }

    @Override
    public void onStart() {
        super.onStart();

        // playボタン（鳥の画像）が押された時の処理
        playBtn = (ImageButton)getActivity().findViewById(R.id.playBtn);
        playBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intentApp = new Intent(getActivity(), AppActivity.class);
                startActivity(intentApp);
            }
        });
    }
}
