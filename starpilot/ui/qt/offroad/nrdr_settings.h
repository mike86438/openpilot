#pragma once

#include "starpilot/ui/qt/offroad/starpilot_settings.h"

// Dedicated top-level NRDR lateral tuning panel. Holds the NRDR Honda EPS /
// angle-PID parameters in a flat, grouped list (no sub-panels). All controls
// use the +/- StarPilotParamValueControl; the PID scales step by 5%.
class StarPilotNrdrPanel : public StarPilotListWidget {
  Q_OBJECT

public:
  explicit StarPilotNrdrPanel(StarPilotSettingsWindow *parent, bool forceOpen = false);

signals:
  void openSubPanel();

private:
  bool forceOpenDescriptions;

  std::map<QString, AbstractControl*> toggles;
};


class StarPilotNrdrLongPanel : public StarPilotListWidget {
  Q_OBJECT

public:
  explicit StarPilotNrdrLongPanel(StarPilotSettingsWindow *parent, bool forceOpen = false);

signals:
  void openSubPanel();

private:
  bool forceOpenDescriptions;

  std::map<QString, AbstractControl*> toggles;
};
