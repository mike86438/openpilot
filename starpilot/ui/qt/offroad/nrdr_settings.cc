#include "starpilot/ui/qt/offroad/nrdr_settings.h"

namespace {

void addHeader(StarPilotListWidget *panel, const QString &text) {
  panel->addItem(new LabelControl(text, "", "", panel));
}

void addValue(std::map<QString, AbstractControl*> &toggles, StarPilotListWidget *panel, const QString &param,
              const QString &title, const QString &desc, float lo, float hi, const QString &suffix,
              float interval, bool fast) {
  AbstractControl *control = new StarPilotParamValueControl(param, title, desc, "", lo, hi, suffix,
                                                            std::map<float, QString>(), interval, fast);
  toggles[param] = control;
  panel->addItem(control);
}

void addToggle(std::map<QString, AbstractControl*> &toggles, StarPilotListWidget *panel, const QString &param,
               const QString &title, const QString &desc) {
  AbstractControl *control = new ParamControl(param, title, desc, "");
  toggles[param] = control;
  panel->addItem(control);
}

void finalizeDescriptions(StarPilotListWidget *panel, bool force_open_descriptions,
                          const std::map<QString, AbstractControl*> &toggles) {
  for (const auto &entry : toggles) {
    AbstractControl *toggle = entry.second;
    QObject::connect(toggle, &AbstractControl::hideDescriptionEvent, [panel]() { panel->update(); });
    QObject::connect(toggle, &AbstractControl::showDescriptionEvent, [panel]() { panel->update(); });
  }

  openDescriptions(force_open_descriptions, toggles);
}

}  // namespace

StarPilotNrdrPanel::StarPilotNrdrPanel(StarPilotSettingsWindow *parent, bool forceOpen) : StarPilotListWidget(parent) {
  forceOpenDescriptions = forceOpen;

  // ---- Low Speed PID (below 25 mph) ----
  addHeader(this, tr("Low Speed PID — Below 25 mph"));
  addValue(toggles, this, "LatPScaleLowSpeed", tr("Low Speed Proportional Scale"), tr("<b>Scales P below 25 mph.</b> Higher is tighter; lower is softer."), 0, 500, tr("%"), 5, true);
  addValue(toggles, this, "LatIScaleLowSpeed", tr("Low Speed Integral Scale"), tr("<b>Scales I below 25 mph.</b> Higher removes steady-state error faster."), 0, 500, tr("%"), 5, true);
  addValue(toggles, this, "LatFScaleLowSpeed", tr("Low Speed Feedforward Scale"), tr("<b>Scales feedforward below 25 mph.</b> 100% preserves the tuned value."), 0, 500, tr("%"), 5, true);

  // ---- Standard Speed PID (25 to 50 mph) ----
  addHeader(this, tr("Standard Speed PID — 25 to 50 mph"));
  addValue(toggles, this, "LatPScaleStandard", tr("Standard Speed Proportional Scale"), tr("<b>Scales P from 25 to 50 mph.</b>"), 0, 500, tr("%"), 5, true);
  addValue(toggles, this, "LatIScaleStandard", tr("Standard Speed Integral Scale"), tr("<b>Scales I from 25 to 50 mph.</b>"), 0, 500, tr("%"), 5, true);
  addValue(toggles, this, "LatFScaleStandard", tr("Standard Speed Feedforward Scale"), tr("<b>Scales feedforward from 25 to 50 mph.</b> 100% preserves the tuned value."), 0, 500, tr("%"), 5, true);

  // ---- Highway PID (above 50 mph) ----
  addHeader(this, tr("Highway PID — Above 50 mph"));
  addValue(toggles, this, "LatPScaleHighway", tr("Highway Proportional Scale"), tr("<b>Scales P above 50 mph.</b>"), 0, 500, tr("%"), 5, true);
  addValue(toggles, this, "LatIScaleHighway", tr("Highway Integral Scale"), tr("<b>Scales I above 50 mph.</b>"), 0, 500, tr("%"), 5, true);
  addValue(toggles, this, "LatFScaleHighway", tr("Highway Feedforward Scale"), tr("<b>Scales feedforward above 50 mph.</b> 100% preserves the tuned value."), 0, 500, tr("%"), 5, true);

  // ---- NRDR Auto Tuning ----
  addHeader(this, tr("NRDR Auto Tuning"));
  addToggle(toggles, this, "NrdrLearnSteerRatio", tr("Learn Steering Ratio"), tr("<b>Use paramsd's learned steering ratio.</b> Turn off to lock to the static car value."));
  addToggle(toggles, this, "NrdrLearnStiffness", tr("Learn Tire Stiffness"), tr("<b>Use paramsd's learned tire stiffness factor.</b> Turn off to use 1.0."));
  addToggle(toggles, this, "NrdrLearnAngleOffset", tr("Learn Angle Offset"), tr("<b>Use paramsd's learned steering angle offset.</b> Turn off to use zero offset."));
  addToggle(toggles, this, "NrdrTuneLearner", tr("2D Online Tune Learner"), tr("<b>Learn a small speed/angle feedforward trim map while driving.</b> Default off; use carefully."));
  addValue(toggles, this, "NrdrTuneLearnerStrength", tr("Tune Learner Strength"), tr("<b>Hard cap for learned trim authority as a percent of full steering output.</b>"), 0, 30, tr("%"), 1, true);
  addValue(toggles, this, "NrdrTuneLearnerRate", tr("Tune Learner Rate"), tr("<b>Learning speed as a percent of the reference rate.</b> 0 freezes learning while still applying the saved map."), 0, 100, tr("%"), 1, true);
  addToggle(toggles, this, "NrdrTuneLearnerReset", tr("Reset Tune Learner Map"), tr("<b>Clear the saved 2D learned trim map.</b> The control clears itself after the reset is processed."));

  // ---- Honda EPS: Center / Unwind ----
  addHeader(this, tr("Honda EPS — Center / Unwind"));
  addValue(toggles, this, "HondaCenterScale", tr("Honda Center Boost"), tr("<b>Adds extra correction near center.</b> Useful when straight roads feel too soft."), 0, 5, QString(), 0.01, false);
  addValue(toggles, this, "HondaCenterBoostThreshold", tr("Honda Center Boost Threshold"), tr("<b>Angle band where center boost is active.</b>"), 0, 10, tr(" deg"), 0.1, false);
  addValue(toggles, this, "HondaCenterBoostMinSpeed", tr("Honda Center Boost Minimum Speed"), tr("<b>Disables center boost below this speed.</b>"), 0, 90, tr(" mph"), 1, true);
  addToggle(toggles, this, "HondaUnwindFreeze", tr("Honda Unwind Integrator Freeze"), tr("<b>Freezes the PID integrator while steering returns toward center.</b>"));
  addToggle(toggles, this, "HondaUnwindLookahead", tr("Honda Unwind Lookahead"), tr("<b>Uses the planned path to start unwind behavior earlier.</b>"));
  addValue(toggles, this, "HondaUnwindBoostSeconds", tr("Honda Unwind Boost Duration"), tr("<b>Limits how long the low-speed unwind feedforward boost is held.</b>"), 0, 3, tr(" s"), 0.1, false);
  addValue(toggles, this, "HondaUnwindFfMultiplier", tr("Honda Unwind Feedforward Multiplier"), tr("<b>Peak low-speed feedforward multiplier during unwind.</b>"), 1, 4, tr("x"), 0.1, false);

  // ---- Honda EPS: Override ----
  addHeader(this, tr("Honda EPS — Override"));
  addToggle(toggles, this, "NrdrIncreaseOverrideTolerance", tr("Increase Driver Override Hysteresis"), tr("<b>Filters short same-direction driver torque spikes.</b>"));
  addValue(toggles, this, "NrdrDriverOverrideThreshold", tr("Driver Override Threshold"), tr("<b>Raw torque threshold for driver steering.</b> 1200 is stock Honda scale."), 100, 5000, QString(), 100, true);
  addValue(toggles, this, "NrdrOverrideThresholdCenterBoost", tr("Center Override Threshold"), tr("<b>Override threshold used inside the center boost angle band.</b>"), 100, 5000, QString(), 100, true);
  addToggle(toggles, this, "HondaDriverAssistDuringOverride", tr("Pass-through Assist During Override"), tr("<b>Drop LKAS torque while the driver is steering.</b>"));
  addValue(toggles, this, "HondaOverrideFadeDownSecs", tr("Override Fade Down"), tr("<b>Seconds to fade steering torque down during override.</b>"), 0, 10, tr(" s"), 0.1, false);
  addValue(toggles, this, "HondaOverrideFadeUpSecs", tr("Override Fade Up"), tr("<b>Seconds to fade steering torque back after override.</b>"), 0, 10, tr(" s"), 0.1, false);
  addValue(toggles, this, "HondaOverrideTorqueScale", tr("Override Torque Retain"), tr("<b>Torque retained after override fade down.</b>"), 0, 100, tr("%"), 1, true);

  // ---- Honda EPS: Filters / Limits ----
  addHeader(this, tr("Honda EPS — Filters / Limits"));
  addToggle(toggles, this, "HondaTorqueLowPassFilter", tr("Honda Torque Low Pass Filter"), tr("<b>Smooths steering torque with speed-banded tau values.</b>"));
  addValue(toggles, this, "HondaLpfTauLowSpeed", tr("Low Speed LPF Tau"), tr("<b>Low-pass tau below 25 mph.</b>"), 0, 5, QString(), 0.01, false);
  addValue(toggles, this, "HondaLpfTauStandard", tr("Standard Speed LPF Tau"), tr("<b>Low-pass tau from 25 to 50 mph.</b>"), 0, 5, QString(), 0.01, false);
  addValue(toggles, this, "HondaLpfTauHighway", tr("Highway LPF Tau"), tr("<b>Low-pass tau above 50 mph.</b>"), 0, 5, QString(), 0.01, false);
  addToggle(toggles, this, "HondaNotchEnabled", tr("Honda Notch Filter"), tr("<b>Removes a narrow EPS chatter band.</b>"));
  addValue(toggles, this, "HondaNotchFreq", tr("Honda Notch Frequency"), tr("<b>Frequency removed from the torque command.</b>"), 1, 20, tr(" Hz"), 0.1, false);
  addValue(toggles, this, "HondaNotchQ", tr("Honda Notch Q"), tr("<b>Width of the removed frequency band.</b> Higher is narrower."), 0.1, 10, QString(), 0.1, false);
  addToggle(toggles, this, "HondaSteerDeltaLimiter", tr("Honda Steer Delta Limiter"), tr("<b>Legacy rate limiter for requested steering torque.</b>"));
  addValue(toggles, this, "HondaSteerDeltaUp", tr("Honda Steer Delta Up"), tr("<b>Maximum upward steering torque rate.</b>"), 0, 100, QString(), 0.1, true);
  addValue(toggles, this, "HondaSteerDeltaDown", tr("Honda Steer Delta Down"), tr("<b>Maximum downward steering torque rate.</b>"), 0, 100, QString(), 0.1, true);
  addValue(toggles, this, "NrdrMinSteerSpeed", tr("Minimum Steer Speed"), tr("<b>No steering torque is commanded below this speed.</b> 0 is stock."), 0, 45, tr(" mph"), 1, true);

  finalizeDescriptions(this, forceOpenDescriptions, toggles);
}

StarPilotNrdrLongPanel::StarPilotNrdrLongPanel(StarPilotSettingsWindow *parent, bool forceOpen) : StarPilotListWidget(parent) {
  forceOpenDescriptions = forceOpen;

  addHeader(this, tr("Honda Longitudinal — PID / Command"));
  addValue(toggles, this, "LongPidTuneScale", tr("Longitudinal PID Tune Scale"), tr("<b>Scales Honda longitudinal PID output.</b> 100% preserves the tuned base values."), 0, 500, tr("%"), 5, true);
  addToggle(toggles, this, "StaticFeedforwardLong", tr("Keep Feedforward Static"), tr("<b>When ON, the longitudinal PID scale multiplies only the feedback terms.</b> Feedforward keeps its tuned value."));
  addToggle(toggles, this, "NrdrHondaEcuMatchedLong", tr("Nidec ECU-Matched Long"), tr("<b>Honda Nidec only.</b> Shapes gas and brake commands closer to the stock ECU with ramp limiting, coasting deadband, and short gas-to-brake handoff coasts."));
  addToggle(toggles, this, "HondaLiveLearningGas", tr("Live Learning Gas"), tr("<b>Adapts Honda gas and wind compensation factors live while driving.</b> Default behavior is OFF for Nidec when the param is unset."));

  addHeader(this, tr("Honda Longitudinal — Stopping"));
  addValue(toggles, this, "HondaStoppingDecelRate", tr("Honda Stopping Decel Rate"), tr("<b>Brake-rate limiter used in Honda carcontroller while coming to a stop.</b> Higher is firmer, lower is softer."), 0, 100, tr("%"), 1, true);
  addValue(toggles, this, "HondaStopAccel", tr("Stop Accel"), tr("<b>Target acceleration once stopped.</b> More negative holds the brake firmer at standstill."), -4, 0, tr(" m/s²"), 0.01, false);
  addValue(toggles, this, "HondaStoppingDecelRateLong", tr("Planner Stopping Rate"), tr("<b>How quickly commanded deceleration ramps down while stopping.</b> Higher slows the car more assertively near the end of a stop."), 0, 5, tr(" m/s²"), 0.01, false);
  addValue(toggles, this, "HondaVEgoStopping", tr("Stop Speed"), tr("<b>Speed below which Honda longcontrol treats the car as stopping.</b>"), 0, 3, tr(" m/s"), 0.01, false);
  addValue(toggles, this, "HondaVEgoStarting", tr("Start Speed"), tr("<b>Speed above which Honda longcontrol treats the car as moving again.</b>"), 0, 3, tr(" m/s"), 0.01, false);

  finalizeDescriptions(this, forceOpenDescriptions, toggles);
}
