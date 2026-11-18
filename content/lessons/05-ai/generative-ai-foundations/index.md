![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Generative AI: Image and Video Training Foundations


## Foundations and practice

Learn pixels, tensors, captions, denoising objectives, video timing, memory budgets and evaluation before planning a model-specific training run.

The conceptual exercises need paper or a calculator and original sample descriptions. Actual model training requires a separately selected compatible trainer and hardware; this course does not claim a native production diffusion trainer.

1. [Start with pixels, frames and generative models](01-pixels-frames-and-models.md)
1. [Prepare image-caption pairs with provenance](02-caption-and-image-pairs.md)
1. [Resize and batch images without silently changing the task](03-resizing-cropping-and-buckets.md)
1. [Understand a denoising objective before training](04-noise-denoising-and-loss.md)
1. [Understand latents, conditioning and image adapters](05-latents-conditioning-and-adapters.md)
1. [Plan and evaluate a small image-training experiment](06-plan-an-image-training-experiment.md)
1. [Prepare video clips with timing and group identity](07-video-timing-and-clip-groups.md)
1. [Evaluate motion and temporal coherence](08-temporal-coherence-and-video-evaluation.md)
1. [Bound memory and recover image/video training work](09-memory-checkpoints-and-recovery.md)
1. [Build a native generative-AI project in verifiable stages](10-native-framework-project-plan.md)

## Native objective practice

1. [Run a native denoising experiment and observe overfitting](11-run-a-native-denoising-experiment.md)

1. [Measure normal noise before using it in a training loop](12-measure-noise-before-training.md)

1. [Distinguish step noise from cumulative signal](13-distinguish-step-noise-from-cumulative-signal.md)

1. [Combine compatible noise predictions and measure guidance](14-combine-compatible-noise-predictions.md)

1. [Follow a deterministic denoising trajectory](15-follow-a-deterministic-denoising-trajectory.md)

1. [Convert diffusion velocity predictions before using them](16-convert-diffusion-velocity-predictions.md)

1. [Exclude padding from a training objective](17-exclude-padding-from-a-training-objective.md)

1. [Weight a training objective deliberately](18-weight-a-training-objective-deliberately.md)

1. [Own the noise in a stochastic denoising step](19-own-the-noise-in-a-stochastic-denoising-step.md)

1. [Read pixels as an explicit tensor](20-read-pixels-as-an-explicit-tensor.md)

1. [Prepare a video sample with explicit frame order](21-prepare-a-video-sample-with-explicit-frame-order.md)

1. [Borrow an image crop with explicit lifetime](22-borrow-an-image-crop-with-explicit-lifetime.md)

1. [Transform pixels without changing their labels by accident](23-transform-pixels-without-changing-their-labels-by-accident.md)

1. [Count image values before preparing training inputs](24-count-image-values-before-preparing-training-inputs.md)

1. [Resize pixels with an explicit sampling rule](25-resize-pixels-with-an-explicit-sampling-rule.md)

1. [Place an image on a canvas without confusing padding and masks](26-place-an-image-on-a-canvas-without-confusing-padding-and-masks.md)

1. [Select video frames by time with an explicit policy](27-select-video-frames-by-time-with-an-explicit-policy.md)

1. [Measure channel means without choosing normalization](28-measure-channel-means-without-choosing-normalization.md)

1. [Apply explicit channel normalization](29-apply-explicit-channel-normalization.md)

1. [Turn model values into explicit pixels](30-turn-model-values-into-explicit-pixels.md)

1. [Validate every frame before publishing a clip](31-validate-every-frame-before-publishing-a-clip.md)

1. [Choose an image interpolation policy](32-choose-an-image-interpolation-policy.md)
