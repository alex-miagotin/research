Absolutely! Here's the **Architecture Overview** rewritten using a clean, easy-to-read **Markdown table** — this format works great in GitHub, GitLab, and most Markdown renderers:

---

## 🧠 Architecture Overview

| Layer                  | Components / Responsibilities                                                                 |
|------------------------|-----------------------------------------------------------------------------------------------|
| **Frontend (UI)**      | - Electron + React<br>- Communicates with backend via TCP socket<br>- Uses Protobuf messages |
| **Communication Layer**| - **CommunicationManager**:<br>  • Routes I/O to/from UI, MQTT, and Serial ports             |
| **Application Core**   | - **Managers**:<br>  • `InstrumentManager`<br>  • `DeviceManager`<br>  • `ProcessManager`<br>  • `ConsumablesManager` |
| **Utilities & Logic**  | - Business logic<br>- State management<br>- Concurrency using `std::thread` and synchronization primitives |
| **Messaging**          | - All communication structured via **Protocol Buffers**                                       |

---

Let me know if you want to include an additional diagram (like a Mermaid chart), or a layered visual using Mermaid or PlantUML!
