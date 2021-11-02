package com.agora.loging

import android.graphics.drawable.ColorDrawable
import android.graphics.drawable.Drawable
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import android.widget.Toast
import androidx.core.content.ContextCompat
import androidx.core.view.isVisible
import com.agora.loging.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        setSdcardPath(getExternalFilesDir("log")?.absolutePath ?: "")

        // Example of a call to a native method
        binding.sampleText.setOnClickListener {
//            val text = stringFromJNI()
//            Toast.makeText(this, text, Toast.LENGTH_SHORT).show()
//            binding.sampleText.text = stringFromJNI()
            Log.d(TAG, "sampleTextColorState = ${binding.sampleText.background.constantState}: ")
            Log.d(TAG, "sampleText2ColorState = ${binding.sampleText2.background.constantState}: ")
            (binding.sampleText.background.mutate() as ColorDrawable).color =
                ContextCompat.getColor(this, R.color.teal_200)
//            (binding.sampleText.background as ColorDrawable).color = ContextCompat.getColor(this, R.color.teal_200)

            binding.sampleText3.isVisible = true
        }
    }

    external fun setSdcardPath(path: String)

    /**
     * A native method that is implemented by the 'loging' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        const val TAG = "[Main]"

        // Used to load the 'loging' library on application startup.
        init {
            System.loadLibrary("loging")
        }
    }
}