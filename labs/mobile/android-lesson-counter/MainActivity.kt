/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/android-lesson-counter/MainActivity.kt
 *
 * PURPOSE:
 *   Present a small Compose learning counter with explicit screen state.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
package org.umicom.learning

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent { MaterialTheme { LessonCounter() } }
    }
}

@Composable
fun LessonCounter() {
    // This screen-local exercise teaches events. A production Umicom client
    // obtains durable progress and policy from a shared Framework service.
    var completed by rememberSaveable { mutableStateOf(0) }
    Column(Modifier.padding(horizontal = 24.dp, vertical = 48.dp)) {
        Text("Umicom learning practice", style = MaterialTheme.typography.headlineSmall)
        Text("Completed: $completed of 3")
        Button(onClick = { if (completed < 3) completed += 1 }, enabled = completed < 3) {
            Text("Complete a practice lesson")
        }
        Button(onClick = { completed = 0 }, enabled = completed > 0) {
            Text("Reset practice")
        }
    }
}
