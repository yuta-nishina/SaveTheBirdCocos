package org.cocos2dx.cpp;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by atgs_mac on 2016/05/31.
 */
public class CharacterDao {

    private static final String TABLE_NAME = "character";
    private static final String COL_NO = "no";
    private static final String COL_NAME = "name";
    private static final String COL_DETAIL = "detail";
    private static final String COL_IMAGE_STAND = "image_stand";
    private static final String[] COLUMNS = {COL_NO, COL_NAME, COL_DETAIL, COL_IMAGE_STAND};

    private SQLiteDatabase db;

    public CharacterDao(SQLiteDatabase db){
        this.db = db;
    }

    public long insert(CharacterData data){
        ContentValues values = new ContentValues();
        values.put(COL_NO, data.getNo());
        values.put(COL_NAME, data.getName());
        values.put(COL_DETAIL, data.getDetail());
        values.put(COL_IMAGE_STAND, data.getImage_stand());
        return db.insert(TABLE_NAME, null, values);
    }

    public int update(CharacterData data){
        ContentValues values = new ContentValues();
        values.put(COL_NO, data.getNo());
        values.put(COL_NAME, data.getName());
        values.put(COL_DETAIL, data.getDetail());
        values.put(COL_IMAGE_STAND, data.getImage_stand());
        String whereClause = "no = " + data.getNo();
        return db.update(TABLE_NAME, values, whereClause, null);
    }

    public List<CharacterData> findAll(){
        List<CharacterData> characterDataList = new ArrayList<CharacterData>();
        Cursor cursor = db.query(TABLE_NAME, COLUMNS, null, null, null, null, COL_NO);
        while (cursor.moveToNext()){
            CharacterData data = new CharacterData();
            data.setNo(cursor.getInt(0));
            data.setName(cursor.getString(1));
            data.setDetail(cursor.getString(2));
            data.setImage_stand(cursor.getString(3));
            characterDataList.add(data);
        }
        cursor.close();
        return characterDataList;
    }

    public CharacterData findByNo(int no){
        String selection = "no = " + no;
        Cursor cursor = db.query(TABLE_NAME, COLUMNS, selection, null, null, null, null);
        CharacterData data = new CharacterData();
        while (cursor.moveToNext()){
            data.setNo(cursor.getInt(0));
            data.setName(cursor.getString(1));
            data.setDetail(cursor.getString(2));
            data.setImage_stand(cursor.getString(3));
        }
        cursor.close();
        return data;
    }

    public int delete(int no){
        return db.delete(TABLE_NAME, "no = " + no, null);
    }
}
