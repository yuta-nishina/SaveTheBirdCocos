package org.cocos2dx.cpp;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class CharacterSelectActivity extends TabActivity {

    ViewPagerIndicator mViewPagerIndicator;
    TextView txtCName;
    TextView txtCDetail;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_character_select);

        // スワイプボックス
        ViewPager mViewPager = (ViewPager)findViewById(R.id.viewpager);
        CustomPagerAdapter mPagerAdapter = new CustomPagerAdapter(this);
        mViewPager.setAdapter(mPagerAdapter);

        // フォント変更
        txtCName = (TextView) findViewById(R.id.charctorName);
        setFontType(txtCName);

        // フォント変更
        txtCDetail = (TextView) findViewById(R.id.charactorDetail);
        setFontType(txtCDetail);

        txtCName.setText("キャラクター 1");
        txtCName.setBackgroundColor(Color.YELLOW);
        txtCDetail.setText("説明 1");
        txtCDetail.setBackgroundColor(Color.YELLOW);

        mViewPagerIndicator = (ViewPagerIndicator) findViewById(R.id.indicator);
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


    }

    /**
     *  キャラ変更アクション
     */
    public void selectCharactor(int position) {
        int pos = position + 1;
        if(pos == 1){
            txtCName.setText("キャラクター "+pos);
            txtCName.setBackgroundColor(Color.YELLOW);
            txtCDetail.setText("説明 "+pos);
            txtCDetail.setBackgroundColor(Color.YELLOW);

        }else if(pos == 2){
            txtCName.setText("キャラクター "+pos);
            txtCName.setBackgroundColor(Color.RED);
            txtCDetail.setText("説明 "+pos);
            txtCDetail.setBackgroundColor(Color.RED);

        }else{
            txtCName.setText("キャラクター "+pos);
            txtCName.setBackgroundColor(Color.BLUE);
            txtCDetail.setText("説明 "+pos);
            txtCDetail.setBackgroundColor(Color.BLUE);

        }

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

            LayoutInflater inflater = (LayoutInflater)getSystemService(Context.LAYOUT_INFLATER_SERVICE);

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
