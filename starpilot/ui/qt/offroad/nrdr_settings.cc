#include "starpilot/ui/qt/offroad/nrdr_settings.h"

StarPilotNrdrPanel::StarPilotNrdrPanel(StarPilotSettingsWindow *parent, bool forceOpen) : StarPilotListWidget(parent) {
  forceOpenDescriptions = forceOpen;

  // Section header (title only).
  auto addHeader = [this](const QString &text) {
    addItem(new LabelControl(text, "", "", this));
  };

  // +/- value control (the PID scales step by 5%).
  auto addValue = [this](const QString &param, const QString &title, const QString &desc,
                         float lo, float hi, const QString &suffix, float interval, bool fast) {
    AbstractControl *control = new StarPilotParamValueControl(param, title, desc, "", lo, hi, suffix,
                                                              std::map<float, QString>(), interval, fast);
    toggles[param] = control;
    addItem(control);
  };

  // On/off toggle.
  auto addToggle = [this](const QString &param, const QString &title, const QString &desc) {
    AbstractControl *control = new ParamControl(param, title, desc, "");
    toggles[param] = control;
    addItem(control);
  };

  // ---- Low Speed PID (below 25 mph) ----
  addHeader(tr("Low Speed PID — Below 25 mph"));
  addValue("LatPScaleLowSpeed", tr("Low Speed Proportional Scale"), tr("<b>Scales P below 25 mph.</b> Higher is tighter; lower is softer."), 0, 500, tr("%"), 5, true);
  addValue("LatIScaleLowSpeed", tr("Low Speed Integral Scale"), tr("<b>Scales I below 25 mph.</b> Higher removes steady-state error faster."), 0, 500, tr("%"), 5, true);
  addValue("LatFScaleLowSpeed", tr("Low Speed Feedforward Scale"), tr("<b>Scales feedforward below 25 mph.</b> 100% preserves the tuned value."), 0, 500, tr("%"), 5, true);

  // ---- Standard Speed PID (25 to 50 mph) ----
  addHeader(tr("Standard Speed PID — 25 to 50 mph"));
  addValue("LatPScaleStandard", tr("Standard Speed Proportional Scale"), tr("<b>Scales P from 25 to 50 mph.</b>"), 0, 500, tr("%"), 5, true);
  addValue("LatIScaleStandard", tr("Standard Speed Integral Scale"), tr("<b>Scales I from 25 to 50 mph.</b>"), 0, 500, tr("%"), 5, true);
  addValue("LatFScaleStandard", tr("Standard Speed Feedforward Scale"), tr("<b>Scales feedforward from 25 to 50 mph.</b> 100% preserves the tuned value."), 0, 500, tr("%"), 5, true);

  // ---- Highway PID (above 50 mph) ----
  addHeader(tr("Highway PID — Above 50 mph"));
  addValue("LatPScaleHighway", tr("Highway Proportional Scale"), tr("<b>Scales P above 50 mph.</b>"), 0, 500, tr("%"), 5, true);
  addValue("LatIScaleHighway", tr("Highway Integral Scale"), tr("<b>Scales I above 50 mph.</b>"), 0, 500, tr("%"), 5, true);
  addValue("LatFScaleHighway", tr("Highway Feedforward Scale"), tr("<b>Scales feedforward above 50 mph.</b> 100% preserves the tuned value."), 0, 500, tr("%"), 5, true);

  // ---- Honda EPS: Center / Unwind ----
  addHeader(tr("Honda EPS — Center / Unwind"));
  addValue("HondaCenterScale", tr("Honda Center Boost"), tr("<b>Adds extra correction near center.</b> Useful when straight roads feel too soft."), 0, 5, QString(), 0.01, false);
  addValue("HondaCenterBoostThreshold", tr("Honda Center Boost Threshold"), tr("<b>Angle band where center boost is active.</b>"), 0, 10, tr(" deg"), 0.1, false);
  addValue("HondaCenterBoostMinSpeed", tr("Honda Center Boost Minimum Speed"), tr("<b>Disables center boost below this speed.</b>"), 0, 90, tr(" mph"), 1, true);
  addToggle("HondaUnwindFreeze", tr("Honda Unwind Integrator Freeze"), tr("<b>Freezes the PID integrator while steering returns toward center.</b>"));
  addToggle("HondaUnwindLookahead", tr("Honda Unwind Lookahead"), tr("<b>Uses the planned path to start unwind behavior earlier.</b>"));
  addValue("HondaUnwindBoostSeconds", tr("Honda Unwind Boost Duration"), tr("<b>Limits how long the low-speed unwind feedforward boost is held.</b>"), 0, 3, tr(" s"), 0.1, false);
  addValue("HondaUnwindFfMultiplier", tr("Honda Unwind Feedforward Multiplier"), tr("<b>Peak low-speed feedforward multiplier during unwind.</b>"), 1, 4, tr("x"), 0.1, false);

  // ---- Honda EPS: Override ----
  addHeader(tr("Honda EPS — Override"));
  addToggle("NrdrIncreaseOverrideTolerance", tr("Increase Driver Override Hysteresis"), tr("<b>Filters short same-direction driver torque spikes.</b>"));
  addValue("NrdrDriverOverrideThreshold", tr("Driver Override Threshold"), tr("<b>Raw torque threshold for driver steering.</b> 1200 is stock Honda scale."), 100, 5000, QString(), 100, true);
  addValue("NrdrOverrideThresholdCenterBoost", tr("Center Override Threshold"), tr("<b>Override threshold used inside the center boost angle band.</b>"), 100, 5000, QString(), 100, true);
  addToggle("HondaDriverAssistDuringOverride", tr("Pass-through Assist During Override"), tr("<b>Drop LKAS torque while the driver is steering.</b>"));
  addValue("HondaOverrideFadeDownSecs", tr("Override Fade Down"), tr("<b>Seconds to fade steering torque down during override.</b>"), 0, 10, tr(" s"), 0.1, false);
  addValue("HondaOverrideFadeUpSecs", tr("Override Fade Up"), tr("<b>Seconds to fade steering torque back after override.</b>"), 0, 10, tr(" s"), 0.1, false);
  addValue("HondaOverrideTorqueScale", tr("Override Torque Retain"), tr("<b>Torque retained after override fade down.</b>"), 0, 100, tr("%"), 1, true);

  // ---- Honda EPS: Filters / Limits ----
  addHeader(tr("Honda EPS — Filters / Limits"));
  addToggle("HondaTorqueLowPassFilter", tr("Honda Torque Low Pass Filter"), tr("<b>Smooths steering torque with speed-banded tau values.</b>"));
  addValue("HondaLpfTauLowSpeed", tr("Low Speed LPF Tau"), tr("<b>Low-pass tau below 25 mph.</b>"), 0, 5, QString(), 0.01, false);
  addValue("HondaLpfTauStandard", tr("Standard Speed LPF Tau"), tr("<b>Low-pass tau from 25 to 50 mph.</b>"), 0, 5, QString(), 0.01, false);
  addValue("HondaLpfTauHighway", tr("Highway LPF Tau"), tr("<b>Low-pass tau above 50 mph.</b>"), 0, 5, QString(), 0.01, false);
  addToggle("HondaNotchEnabled", tr("Honda Notch Filter"), tr("<b>Removes a narrow EPS chatter band.</b>"));
  addValue("HondaNotchFreq", tr("Honda Notch Frequency"), tr("<b>Frequency removed from the torque command.</b>"), 1, 20, tr(" Hz"), 0.1, false);
  addValue("HondaNotchQ", tr("Honda Notch Q"), tr("<b>Width of the removed frequency band.</b> Higher is narrower."), 0.1, 10, QString(), 0.1, false);
  addToggle("HondaSteerDeltaLimiter", tr("Honda Steer Delta Limiter"), tr("<b>Legacy rate limiter for requested steering torque.</b>"));
  addValue("HondaSteerDeltaUp", tr("Honda Steer Delta Up"), tr("<b>Maximum upward steering torque rate.</b>"), 0, 100, QString(), 0.1, true);
  addValue("HondaSteerDeltaDown", tr("Honda Steer Delta Down"), tr("<b>Maximum downward steering torque rate.</b>"), 0, 100, QString(), 0.1, true);
  addValue("NrdrMinSteerSpeed", tr("Minimum Steer Speed"), tr("<b>No steering torque is commanded below this speed.</b> 0 is stock."), 0, 45, tr(" mph"), 1, true);

  // Repaint when a description is expanded or collapsed.
  for (auto &entry : toggles) {
    AbstractControl *toggle = entry.second;
    QObject::connect(toggle, &AbstractControl::hideDescriptionEvent, [this]() { update(); });
    QObject::connect(toggle, &AbstractControl::showDescriptionEvent, [this]() { update(); });
  }

  openDescriptions(forceOpenDescriptions, toggles);
}
