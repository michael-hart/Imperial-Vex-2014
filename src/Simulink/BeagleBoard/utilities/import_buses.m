function import_buses()

    load create_packetsbus.mat;
    % Can't save bus as variable size, so load as fixed and set manually
    for jj = 1:5
        PacketsBus.Elements(jj).DimensionsMode = 'Variable'; %#ok<STRNU>
    end
    clearvars jj;
end