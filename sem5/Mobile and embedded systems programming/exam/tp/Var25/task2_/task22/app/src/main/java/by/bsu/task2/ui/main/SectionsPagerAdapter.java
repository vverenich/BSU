package by.bsu.task2.ui.main;

import android.content.Context;
import android.os.Bundle;

import androidx.annotation.Nullable;
import androidx.annotation.StringRes;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;

import by.bsu.task2.R;

public class SectionsPagerAdapter extends FragmentPagerAdapter {
    @StringRes
    private static final int[] TAB_TITLES = new int[]{R.string.title_section1, R.string.title_section2,
            R.string.title_section3};
    private final Context mContext;

    public SectionsPagerAdapter(Context context, FragmentManager fm) {
        super(fm);
        mContext = context;
    }

    @Override
    public Fragment getItem(int position) {
        // getItem is called to instantiate the fragment for the given page.
        // Return a PlaceholderFragment (defined as a static inner class below).
        Fragment fragment=null;
        Bundle args;
        switch (position) {
            case 0:
                fragment = new FirstActivity();
                args = new Bundle();
                args.putInt(FirstActivity.ARG_SECTION_NUMBER, position + 1);
                fragment.setArguments(args);
                break;
            case 1:
                fragment = new SecondActivity();
                args = new Bundle();
                args.putInt(SecondActivity.ARG_SECTION_NUMBER, position +
                        1);
                fragment.setArguments(args);
                break;
            case 2:
                fragment = new ThirdActivity();
                args = new Bundle();
                args.putInt(ThirdActivity.ARG_SECTION_NUMBER, position + 1);
                fragment.setArguments(args);
                break;
        }
        return fragment;
    }

    @Nullable
    @Override
    public CharSequence getPageTitle(int position) {
        return mContext.getResources().getString(TAB_TITLES[position]);
    }

    @Override
    public int getCount() {
        return TAB_TITLES.length;
    }
}
