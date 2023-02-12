package by.bsu.task2.ui.main;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;

import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.List;

import by.bsu.task2.R;

public class ImageAdapter extends BaseAdapter {

    private Context mContext;

    public ImageAdapter(Context c) {
        mContext = c;
    }

    private final List<Integer> images = Arrays.asList(
            R.drawable.first, R.drawable.second,
            R.drawable.third, R.drawable.fourth
    );

    @Override
    public int getCount() {
        return images.size();
    }

    @Override
    public Object getItem(int position) {
        return images.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ImageView imageView;
        if (convertView == null) {
            // if it's not recycled, initialize some attributes
            imageView = new ImageView(mContext);
            imageView.setLayoutParams(new GridView.LayoutParams(385, 385));
            imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
            imageView.setPadding(8, 8, 8, 8);
        } else {
            imageView = (ImageView) convertView;
        }

        imageView.setImageResource(images.get(position));
        return imageView;
    }
}
