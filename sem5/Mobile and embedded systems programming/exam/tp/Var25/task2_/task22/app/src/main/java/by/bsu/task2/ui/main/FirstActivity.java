package by.bsu.task2.ui.main;

import static android.content.Context.MODE_PRIVATE;

import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.content.SharedPreferences;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import java.util.Calendar;

import by.bsu.task2.R;

/**
 * A placeholder fragment containing a simple view.
 */
public class FirstActivity extends Fragment {
    private SharedPreferences sharedPreferences;
    private SharedPreferences.OnSharedPreferenceChangeListener listener;

    private ImageView imageView;
    private Button buttonAnimation;

    public static final String ARG_SECTION_NUMBER = "section_number";

    public static FirstActivity newInstance() {
        FirstActivity fragment = new FirstActivity();
        Bundle bundle = new Bundle();
        fragment.setArguments(bundle);
        return fragment;
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        View v = getView();
        sharedPreferences = getContext().getSharedPreferences("figures", MODE_PRIVATE);

        buttonAnimation = v.findViewById(R.id.buttonAnimation);

        buttonAnimation.setOnClickListener(v1 -> {
            String uri = "@drawable/triang";
            int imageResource = getResources().getIdentifier(uri, null, getActivity().getPackageName());

            imageView = v.findViewById(R.id.imageView);
            Animation animationRotationTransformation = AnimationUtils.loadAnimation(getContext(), R.anim.animation_rotation_transformation);
            imageView.startAnimation(animationRotationTransformation);

            Drawable res = getResources().getDrawable(imageResource);
            imageView.setImageDrawable(res);
        });

        listener = (sharedPreferences, key) -> {
            String selectedFigure = sharedPreferences.getString("selected_figure", "Circle");

            String uri = "@drawable/triang";
            /*
            switch (selectedFigure) {
                case "Circle":
                    uri = "@drawable/circle";
                    break;
                case "Square":
                    uri = "@drawable/square";
                    break;
                case "Five pointed star":
                    uri = "@drawable/star";
                    break;
            }
            */

            int imageResource = getResources().getIdentifier(uri, null, getActivity().getPackageName());

            imageView = v.findViewById(R.id.imageView);
            Animation animationRotationTransformation = AnimationUtils.loadAnimation(getContext(), R.anim.animation_rotation_transformation);
            imageView.startAnimation(animationRotationTransformation);

            Drawable res = getResources().getDrawable(imageResource);
            imageView.setImageDrawable(res);
        };
        sharedPreferences.registerOnSharedPreferenceChangeListener(listener);
    }


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {

        return inflater.inflate(R.layout.first_tab, container, false);
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
    }
}