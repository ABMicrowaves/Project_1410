using atpLib.Scenarios;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using atpLib.Devices;
using pc_gui.Messages;
using System.IO;
using System.Threading;

namespace pc_gui.Scenarios
{
    public class StatusScenario : SingleDeviceScenario
    {
        public delegate void updateStatusDelegate(GetStatusResponse status);

        updateStatusDelegate updateFunc;
        public StatusScenario(string name, Device device, updateStatusDelegate updateFunc) : base(name, device)
        {
            this.updateFunc = updateFunc;
        }

        protected override ScenarioResult internalRun(CancellationToken ct)
        {
            try
            {
                /* check that the device is alive */
                new SingleMessageSingleDeviceScenario("Get Status Scenario", new GetStatusMessage(), true, false, device).run(DEFAULT_TIMEOUT);

                while(!ct.IsCancellationRequested)
                {
                    /* once in 1 seconds */

                    Scenario.ScenarioResult result = new SingleMessageSingleDeviceScenario("Get Status", new GetStatusMessage(), true, false, device).run(2000);
                    if (result == null || result.result != ScenarioResult.RunResult.Pass)
                    { 
                        log.Error("Error reading Status from card!");
                        break;
                    } else
                    {
                        GetStatusResponse resp = (GetStatusResponse)result.resultObj;
                        updateFunc.Invoke(resp);
                    }

                    System.Threading.Thread.Sleep(50);
                }

                return new ScenarioResult(ScenarioResult.RunResult.Canceled, null);
            }
            catch (Exception ex)
            {
                log.Error("error in \"Get Status Scenario\"", ex);
                return new ScenarioResult(ScenarioResult.RunResult.Fail, null);
            }

        }
    }
}
