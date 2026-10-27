# Native three-worker FedAvg laboratory

This practical exercise calls the **shared Umicom Framework C23 API**. It does not duplicate averaging, source parsing, checkpoint hashing or network transport inside Bits2Banking.

A scalar base parameter of 1.000 receives three *synthetic* local model deltas: +0.050 (100 distinct examples), −0.010 (250), and +0.080 (150). The weighted delta is +0.029, giving a candidate scalar of 1.029. This is arithmetic only: it does not assert the model was trained, learned anything useful or has passed evaluation.

Use CMake and Ninja to build the lab against a Framework source checkout with `UMICOM_FRAMEWORK_SOURCE` set to the repository root. Run the registered CTest. Compare the output with the worked calculation in Lessons 378 and Mathematics Unit 233.

**Research challenges:** change sample weights; inject a duplicated contributor ID; try a mismatched base digest; inspect the exact status before and after rejection; explain why these checks do not prevent data poisoning or fabricate a blockchain consensus proof.

Original code: Sammy Hegab / Umicom Foundation. MIT.
