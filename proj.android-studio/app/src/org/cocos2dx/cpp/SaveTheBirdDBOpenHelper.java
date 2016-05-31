package org.cocos2dx.cpp;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * Created by atgs_mac on 2016/05/31.
 */
public class SaveTheBirdDBOpenHelper extends SQLiteOpenHelper {

    /* データベース名 */
    static final String DB_NAME = "save_the_bird.db";
    /* データベースのバージョン */
    static final int DB_VERSION = 1;
    /* CharacterテーブルのCreate文 */
    static final String CREATE_TABLE_CHARACTER = "create table character "
            +"(no integer, name text, detail text, image_stand text);";
    /* CharacterテーブルのDrop文 */
    static final String DROP_TABLE_CHARACTER = "drop table if exists character";

    public SaveTheBirdDBOpenHelper(Context context){
        super(context, DB_NAME, null,DB_VERSION);
    }

    // 最初にDBが読み込まれる時に一回だけ呼ばれる
    @Override
    public void onCreate(SQLiteDatabase db) {
        // Characterテーブルの作成
        db.execSQL(CREATE_TABLE_CHARACTER);

        // 初期データの挿入
        CharacterDao dao = new CharacterDao(db);
        // キャラクター１
        CharacterData chara1 = new CharacterData();
        chara1.setNo(1);
        chara1.setName("image/chara/chara01/chara01_name.png");
        chara1.setDetail("キャラクター１の説明です");
        chara1.setImage_stand("image/chara/chara01/chara01_front_stand.png");
        dao.insert(chara1);
        // キャラクター２
        CharacterData chara2 = new CharacterData();
        chara2.setNo(2);
        chara2.setName("image/chara/chara02/chara02_name.png");
        chara2.setDetail("キャラクター２の説明です");
        chara2.setImage_stand("image/chara/chara02/chara02_front_stand.png");
        dao.insert(chara2);
        // キャラクター３
        CharacterData chara3 = new CharacterData();
        chara3.setNo(3);
        chara3.setName("image/chara/chara03/chara03_name.png");
        chara3.setDetail("キャラクター３の説明です");
        chara3.setImage_stand("image/chara/chara03/chara03_front_stand.png");
        dao.insert(chara3);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL(DROP_TABLE_CHARACTER);
        onCreate(db);
    }
}
