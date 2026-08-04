import {
  Group,
  Select,
  Stack,
  Container,
  TextInput,
} from "@mantine/core";
import { ProgressReport, ReportUnit } from "./progress";
import { prettyPercent } from "./helpers";
import { ProgressBar, ProgressBarProps } from "./ProgressBar";
import { FileHeatmap } from "./FileHeatmap";

import "./css/app.css";
import { SourceFileInfo } from "./File";
import { useState } from "react";
import { FileMetric, metricData } from "./FileMetric";
import { PERCENT_PUSHES } from "./percent_push";

export function OverallProgress() {
  const total_percent = ProgressReport.matched_code_percent;
  const fuzzy_percent = ProgressReport.fuzzy_match_percent;
  const [unit, setUnit] = useState<ReportUnit | undefined>(
    ProgressReport.units[0]
  );
  const [sortMetric, setSortMetric] = useState<FileMetric | null>(null);
  const [highlightMetric, setHighlightMetric] = useState<FileMetric | null>(
    FileMetric.FuzzyPercent
  );
  const [fileFilter, setFileFilter] = useState("");
  const [functionFilter, setFunctionFilter] = useState("");

  const progressBar: ProgressBarProps = {
    size: 40,
    current: {
      percentage: ProgressReport.matched_code_percent,
    },
    fuzzy: {
      percentage: fuzzy_percent,
    },
    milestones: PERCENT_PUSHES,
  };

  // Filter units by top-level folder (excluding auto-generated)
  const nonAutoUnits = ProgressReport.units.filter(
    (x) => !x.metadata?.auto_generated
  );
  const spyroUnits = nonAutoUnits.filter((x) =>
    x.name.toLowerCase().includes("spyro/")
  );
  const engineXUnits = nonAutoUnits.filter((x) =>
    x.name.toLowerCase().includes("enginex/")
  );
  const platformUnits = nonAutoUnits.filter(
    (x) =>
      !x.name.toLowerCase().includes("spyro/") &&
      !x.name.toLowerCase().includes("enginex/")
  );

  const allFolders = [
    {
      name: "Spyro Game Code",
      units: spyroUnits,
    },
    {
      name: "Engine X",
      units: engineXUnits,
    },
    {
      name: "Platform & System Code",
      units: platformUnits,
    },
  ];

  const onFileClick = (name: string) => {
    const unit = ProgressReport.units.find((x) => x.name === name);
    setUnit(unit);
  };

  function getUnits(units: ReportUnit[]): ReportUnit[] {
    const fileFiltered = !fileFilter
      ? units
      : units.filter((u) =>
          u.name.toLowerCase().includes(fileFilter.toLowerCase())
        );

    const filtered = !functionFilter
      ? fileFiltered
      : fileFiltered.filter((u) =>
          u.functions
            ?.flatMap((fn) => fn)
            .some(
              (fn) =>
                fn.name.toLowerCase().includes(functionFilter.toLowerCase()) ||
                fn.metadata?.demangled_name
                  ?.toLowerCase()
                  .includes(functionFilter.toLowerCase())
            )
        );

    if (!sortMetric) return filtered;
    const { value } = metricData[sortMetric];
    return filtered.sort((a, b) => value(b) - value(a));
  }

  return (
    <Container id="main" size={"lg"}>
      <Stack gap={"md"}>
        <div>
          <h1>
            Spyro: A Hero's Tail is {prettyPercent(fuzzy_percent)}{" "}
            decompiled
          </h1>
          <ProgressBar {...progressBar} />
        </div>
        <Group grow gap={"lg"} align={"flex-start"}>
          <Stack gap={"sm"}>
            <Group grow>
              <TextInput
                value={fileFilter}
                onChange={(event) => setFileFilter(event.currentTarget.value)}
                label="File Name Filter"
                placeholder="Filter by file name"
              />
              <TextInput
                value={functionFilter}
                onChange={(event) =>
                  setFunctionFilter(event.currentTarget.value)
                }
                label="Function Name Filter"
                placeholder="Filter by function name"
              />
            </Group>
            <Group grow>
              <Select
                label="File Sort Metric"
                data={Object.entries(metricData).map(([key, data]) => ({
                  label: data.description,
                  value: key,
                }))}
                value={sortMetric}
                onChange={(value) => setSortMetric(value as FileMetric)}
              />
              <Select
                label="Highlight Metric"
                data={Object.entries(metricData).map(([key, data]) => ({
                  label: data.description,
                  value: key,
                }))}
                value={highlightMetric}
                onChange={(value) => setHighlightMetric(value as FileMetric)}
              />
            </Group>
            <Stack>
              {allFolders.map((folder, index) => (
                <FileHeatmap
                  key={index}
                  folderName={folder.name}
                  filteredUnits={getUnits(folder.units)}
                  allUnits={allFolders.flatMap((x) => x.units)}
                  onClick={onFileClick}
                  metric={
                    metricData[highlightMetric ?? FileMetric.FuzzyPercent]
                  }
                />
              ))}
            </Stack>
          </Stack>
          {unit && <SourceFileInfo unit={unit} />}
        </Group>
      </Stack>
    </Container>
  );
}
