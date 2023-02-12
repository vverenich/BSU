package by.bsu.task2.ui.main;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TabHost;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import static android.content.Context.MODE_PRIVATE;

import com.google.android.material.tabs.TabLayout;

import by.bsu.task2.R;

/**
 * A placeholder fragment containing a simple view.
 */
public class SecondActivity extends Fragment {

    private Button okButton;
    private Button cancelButton;
    private TextView bestTextView;

    public static final String ARG_SECTION_NUMBER = "section_number";

    public static SecondActivity newInstance(int index) {
        SecondActivity fragment = new SecondActivity();
        Bundle bundle = new Bundle();
        bundle.putInt(ARG_SECTION_NUMBER, index);
        fragment.setArguments(bundle);
        return fragment;
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        View v = getView();

        Spinner spinner = v.findViewById(R.id.spinner);
        okButton = v.findViewById(R.id.okButton);

        okButton.setOnClickListener(v1 -> {
            String selectedItem = spinner.getSelectedItem().toString();
            TextView bestTextView = v.findViewById(R.id.bestTextView);
            bestTextView.setText(selectedItem);
        });
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {

        return inflater.inflate(R.layout.second_tab, container, false);
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
    }
}