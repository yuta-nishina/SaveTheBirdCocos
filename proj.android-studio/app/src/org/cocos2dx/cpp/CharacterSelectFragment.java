package org.cocos2dx.cpp;

import android.app.Activity;
import android.app.Fragment;
import android.content.Context;
import android.content.SharedPreferences;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.annotation.Nullable;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.IOException;
import java.util.List;

public class CharacterSelectFragment extends Fragment {

    private ViewPagerIndicator mViewPagerIndicator;
    private ImageView imageCName;
    private TextView txtCDetail;

    private MainActivity activity;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_character_select,container,false);
    }

    @Override
    public void onStart() {
        super.onStart();

        // アクティビティのメソッドを使うためにインスタンス化
        activity = (MainActivity) getActivity();

        // スワイプボックス
        ViewPager mViewPager = (ViewPager)activity.findViewById(R.id.viewpager);
        CustomPagerAdapter mPagerAdapter = new CustomPagerAdapter(activity);
        mViewPager.setAdapter(mPagerAdapter);

        // キャラクター名表示部（ImageView）のインスタンス化
        imageCName = (ImageView) activity.findViewById(R.id.charctorName);

        // フォント変更
        txtCDetail = (TextView)activity.findViewById(R.id.charactorDetail);
        activity.setFontType(txtCDetail);

        mViewPagerIndicator = (ViewPagerIndicator)activity.findViewById(R.id.indicator);
        mViewPagerIndicator.setCount(mPagerAdapter.getCount());
        mViewPager
                .setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
                    @Override
                    public void onPageSelected(int position) {
                        selectCharactor(position);
                        super.onPageSelected(position);
                        mViewPagerIndicator.setCurrentPosition(position);
                    }
                });

        // ユーザが前回選択したキャラクターを取得する
        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(activity);
        int currentCharaPosition = preferences.getInt("current_charactor_no", 1) - 1; // キャラクター番号 - 1
        // 取得したキャラクターの位置にスクロールする
        mViewPager.setCurrentItem(currentCharaPosition);
        // 名前と説明文を変更する
        selectCharactor(currentCharaPosition);
    }

    /**
     *  キャラ変更アクション
     */
    public void selectCharactor(int position) {

        // キャラクターの名前を更新
        try {
            imageCName.setImageBitmap(activity.loadBitmapFromAsset(activity.characterDataList.get(position).getName()));
        } catch (IOException e) {
            e.printStackTrace();
        }
        // キャラクターの説明文を更新
        txtCDetail.setText(activity.characterDataList.get(position).getDetail());

        // 設定値を保存
        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(getActivity());
        preferences.edit().putInt("current_charactor_no", position + 1).apply();

    }

    /**
     *  カスタムアダプター
     */
    private class CustomPagerAdapter extends PagerAdapter {

        int[] pages = {R.layout.char1, R.layout.char2, R.layout.char3};
        Context mContext;

        public CustomPagerAdapter(Context context) {
            mContext = context;
        }

        // ページ数
        @Override
        public int getCount() {
            return pages.length;
        }

        @Override
        public boolean isViewFromObject(View v, Object o) {
            return v.equals(o);
        }

        // ページ切替
        @Override
        public Object instantiateItem(ViewGroup container, int position) {

            LayoutInflater inflater = (LayoutInflater)activity.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

            View layout ;
            layout = inflater.inflate(pages[position], null);
            ((ViewPager) container).addView(layout);
            return layout;

        }

        // 削除
        @Override
        public void destroyItem(ViewGroup container, int position, Object object) {
            ((ViewPager)container).removeView((View)object);
        }
    }



}
