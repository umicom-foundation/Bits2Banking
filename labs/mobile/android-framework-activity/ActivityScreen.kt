/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/android-framework-activity/ActivityScreen.kt
 *
 * PURPOSE:
 *   Present shared C activity results in an Android Compose screen.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

package org.umicom.learning.activity

import androidx.compose.foundation.layout.Column
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue

@Composable
fun ActivityScreen() {
    var completed by rememberSaveable { mutableStateOf(0) }
    var message by rememberSaveable { mutableStateOf("Ready") }
    Column {
        Text("Completed exercises: $completed")
        Button(onClick = {
            // Kotlin owns presentation; C owns the application transition.
            val next = NativeActivity.next(completed)
            if (next >= 0) {
                completed = next
                message = "Exercise recorded"
            } else {
                message = "No change: check the count or begin another activity"
            }
        }) { Text("Complete exercise") }
        Text(message)
    }
}

