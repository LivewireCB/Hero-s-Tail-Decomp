import rawProgress from "../json/progress.json";

const raw = rawProgress as any;

// Adapt standard objdiff report.json to the shape the website expects
export const ProgressReport: Report = {
  units: raw.units,
  version: raw.version ?? 1,
  categories: raw.categories ?? [],
  total_code: Number(raw.measures?.total_code ?? 0),
  total_data: Number(raw.measures?.total_data ?? 0),
  total_functions: raw.measures?.total_functions ?? 0,
  matched_code: Number(raw.measures?.matched_code ?? 0),
  matched_data: Number(raw.measures?.matched_data ?? 0),
  matched_functions: raw.measures?.matched_functions ?? 0,
  fuzzy_match_percent: raw.measures?.fuzzy_match_percent ?? 0,
  matched_code_percent: raw.measures?.matched_code_percent ?? 0,
  matched_data_percent: raw.measures?.matched_data_percent ?? 0,
  matched_functions_percent: raw.measures?.matched_functions_percent ?? 0,
};

// Project progress report
export type Report = {
  units: ReportUnit[];
  version: number;
  categories: ReportCategory[];

  total_code: number;
  total_data: number;
  total_functions: number;
  matched_code: number;
  matched_data: number;
  matched_functions: number;
  fuzzy_match_percent: number;
  matched_code_percent: number;
  matched_data_percent: number;
  matched_functions_percent: number;
};

// Progress info for a report or unit
export type Measures = {
  fuzzy_match_percent: number;
  total_code?: string;
  matched_code?: string;
  matched_code_percent: number;
  total_data: string;
  matched_data?: string;
  matched_data_percent: number;
  total_functions: number;
  matched_functions: number;
  matched_functions_percent: number;
  complete_code: string;
  complete_code_percent: number;
  complete_data: string;
  complete_data_percent: number;
  total_units: number;
  complete_units: number;
};

// Progress category
export type ReportCategory = {
  id: string;
  name: string;
  measures: Measures;
};

// A unit of the report (usually a translation unit)
export type ReportUnit = {
  name: string;
  measures: Measures;
  sections?: ReportItem[];
  functions?: ReportItem[];
  metadata?: ReportUnitMetadata;
};

// Extra metadata for a unit
export type ReportUnitMetadata = {
  complete?: boolean;
  module_name?: string;
  module_id?: number;
  source_path?: string;
  progress_categories: string[];
  auto_generated?: boolean;
};

// A section or function within a unit
export type ReportItem = {
  name: string;
  size: string;
  fuzzy_match_percent: number;
  metadata?: ReportItemMetadata;
  opcodes?: string[];
  labels?: number;
};

// Extra metadata for an item
export type ReportItemMetadata = {
  demangled_name?: string;
  virtual_address?: string;
};
