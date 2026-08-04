import React from "react";
import ReactDOM from "react-dom/client";
import App from "./App.tsx";

// core styles are required for all packages
import "@mantine/core/styles.css";
import "@mantine/charts/styles.css";
import "@mantine/code-highlight/styles.css";
import "@mantine/notifications/styles.css";

import { MantineProvider, createTheme } from "@mantine/core";
import { HashRouter } from "react-router-dom";
import { Notifications } from "@mantine/notifications";

const theme = createTheme({
  //
});

ReactDOM.createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
    <HashRouter>
      <MantineProvider theme={theme} defaultColorScheme={"dark"}>
        <Notifications />
        <App />
      </MantineProvider>
    </HashRouter>
  </React.StrictMode>
);
